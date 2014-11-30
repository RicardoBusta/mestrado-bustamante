#include "glwidget.h"

#include <QMouseEvent>
#include <QWheelEvent>

#include <QTimer>

#include "programs/CG1/opengl/textures.h"
#include "programs/CG1/utils/options.h"
#include "programs/CG1/opengl/shaders.h"

#include <QMessageBox>
#include <QFileDialog>

GLWidget::GLWidget(QWidget *parent) :
  QGLWidget(parent),
  timer_( new QTimer(this) )
{
  Textures::instance()->setGlWidget(this);

  connect(timer_,SIGNAL(timeout()),this,SLOT(sceneStep()));
  connect(timer_,SIGNAL(timeout()),this,SLOT(updateGL()));
  timer_->start(1000/60);
}

GLWidget::~GLWidget()
{

}

void GLWidget::setShaders(const QString &vert_shader, const QString &frag_shader)
{
  bool success = true;

  shader_program_.removeAllShaders();
  success = shader_program_.addShaderFromSourceCode(QGLShader::Vertex, vert_shader);
  if(!success){
    popUpLogMessage(shader_program_.log());
  }

  success = shader_program_.addShaderFromSourceCode(QGLShader::Fragment, frag_shader);
  if(!success){
    popUpLogMessage(shader_program_.log());
  }

  success = shader_program_.link();
  if(!success){
    popUpLogMessage(shader_program_.log());
  }
}

void GLWidget::releaseShader()
{
  shader_program_.removeAllShaders();
}

void GLWidget::initializeGL()
{
  Scene::initialize();
  //  Scene::current()->initialize();

  shader_program_.removeAllShaders();
}

void GLWidget::resizeGL(int w, int h)
{
  if(!Scene::valid()) return;

  Scene::current()->resize(w,h);
}

void GLWidget::paintGL()
{
  if(!Scene::valid()) return;

  Scene::current()->setOptions();

  Scene::current()->rotate(auto_delta_.y(),auto_delta_.x(),0);

  Scene::current()->clear();
  Scene::current()->applyCameraConstraint();
  Scene::current()->pre_draw();
  if(shader_program_.isLinked()) shader_program_.bind();
  Scene::current()->draw();
  if(shader_program_.isLinked()) shader_program_.release();
  Scene::current()->post_draw();
  Scene::current()->drawArtifacts();

  while(GLenum err= glGetError()){
    qDebug() << "GL Error:" << err;
  }
}

void GLWidget::popUpLogMessage(QString msg)
{
  QMessageBox m_box;
  m_box.setText(msg);
  m_box.exec();
}


void GLWidget::mousePressEvent(QMouseEvent *event)
{
  if(!Scene::valid()) return;

  auto_delta_ = QPoint(0,0);
  last_click_ = event->pos();

  event->accept();
}


void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
  if(!Scene::valid()) return;

  if(delta_.manhattanLength() > 5){
    auto_delta_ = delta_*Options::instance()->rot_to_angle();
  }else{
    auto_delta_ = QPoint(0,0);
  }

  event->accept();
}


void GLWidget::wheelEvent(QWheelEvent *event)
{
  if(!Scene::valid()) return;

  Scene::current()->addZoom( event->delta() );

  event->accept();
}


void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
  if(!Scene::valid()) return;

  delta_ = event->pos()-last_click_;
  last_click_ = event->pos();
  if(event->buttons() & Qt::LeftButton){
    Scene::current()->rotate(delta_.y(),delta_.x(),0);
  }

  event->accept();
}

void GLWidget::sceneStep()
{
  if(!Scene::valid()) return;

  Scene::current()->step();
}

void GLWidget::exportFrameBuffer()
{
  qDebug() << "export";

  QString save_name = QFileDialog::getSaveFileName(this,"Save Image","","Images (*.png *.jpg)");
  if(!save_name.isEmpty()){
    QImage img = grabFrameBuffer(false);
    img.save(save_name);
  }
}
