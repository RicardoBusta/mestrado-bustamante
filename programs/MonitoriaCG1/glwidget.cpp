#include "glwidget.h"

#include <QDebug>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QTimer>
#include <QFileDialog>
#include <QImage>
#include <QMessageBox>
#include <QString>

const float kRotDeltaToAngle = 0.5f;
const float kAutoDeltaToAngle = 0.1f;
const float kZoomDeltaToAngle = 0.001f;

GLWidget::GLWidget(QWidget *parent)
  : QGLWidget(parent),
    models_(NULL),
    zoom_(0.5),
    rotx_(0),
    roty_(0),
    timer_(new QTimer(this)),
    perspective_(false),
    initialized_(false){
  timer_->setInterval(1000/60);
  QObject::connect(timer_,SIGNAL(timeout()),this,SLOT(AutoRotate()));
}

GLWidget::~GLWidget()
{

}

void GLWidget::SetModelRef(ModelMap *models) {
  models_ = models;
}

void GLWidget::initializeGL() {
  if(initialized_){
    return;
  }
  initialized_ = true;
  qDebug() << "initialize";
  glClearColor(0.5f,0.5f,0.5f,1.0f);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  glEnable(GL_CULL_FACE);
  glEnable(GL_TEXTURE_2D);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1,1,-1,1,-100,100);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Create Basic Texture
  QImage img(QSize(16,16),QImage::Format_ARGB32);
  for(int i=0;i<16;i++){
    for(int j=0;j<16;j++){
      unsigned int color = 0xff000000;
      if(i==j || i==15-j){
        color = 0xffffffff;
      }else if(i==0||j==0||i==15||j==15){
        color = 0xff000000;
      }else if(i>j){
        if(15-i>j){
          color = 0xffff9900;
        }else{
          color = 0xff0099ff;
        }
      }else{
        if(15-i>j){
          color = 0xff00ff99;
        }else{
          color = 0xffff0099;
        }
      }
      img.setPixel(i,j,color);
    }
  }
  bindTexture(img,GL_TEXTURE_2D,GL_RGBA32F,QGLContext::NoBindOption);
}

void GLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
  if(NULL == models_){
    return;
  }

  glLoadIdentity();
  glScalef(zoom_,zoom_,zoom_);
  glRotatef(rotx_,1,0,0);
  glRotatef(roty_,0,1,0);

  foreach(const Model &m, *models_){
    m.Draw();
  }
}

void GLWidget::resizeGL(int w, int h) {
  glViewport(0,0,w,h);
  float ratio = static_cast<float>(w)/static_cast<float>(h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if(perspective_){
    glFrustum(-0.1*ratio,0.1*ratio,-0.1,0.1,0.01,1000.0);
    glTranslatef(0,0,-5);
  }else{
    glOrtho(-1*ratio,1*ratio,-1,1,-100,100);
  }
  glMatrixMode(GL_MODELVIEW);
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
  auto_delta_ = QPoint(0,0);
  last_click_ = event->pos();
  timer_->stop();

  event->accept();

  update();
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event) {
  if(delta_.manhattanLength() > 5){
    auto_delta_ = delta_*kAutoDeltaToAngle;
    timer_->start();
  }else{
    auto_delta_ = QPoint(0,0);
  }

  event->accept();

  update();
}

void GLWidget::wheelEvent(QWheelEvent *event) {
  zoom_ += event->delta() * zoom_ * kZoomDeltaToAngle;

  event->accept();

  update();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
  delta_ = event->pos()-last_click_;
  last_click_ = event->pos();
  if(event->buttons() & Qt::LeftButton){
    rotx_ += delta_.y() * kRotDeltaToAngle;
    roty_ += delta_.x() * kRotDeltaToAngle;
  }

  event->accept();

  update();
}

void GLWidget::SetShaders(const QString &v_shader, const QString &f_shader) {
  bool error = false;
  QString error_str = "";

  error = shader_program_.addShaderFromSourceCode(QGLShader::Vertex,"void main(){}");
  if(error){
    error_str += shader_program_.log()+"\n";
  }
  error = shader_program_.addShaderFromSourceCode(QGLShader::Fragment,"");
  if(error){
    error_str += shader_program_.log()+"\n";
  }
  error = shader_program_.link();
  if(error){
    error_str += shader_program_.log()+"\n";
  }
  error = shader_program_.bind();
  if(error){
    error_str += shader_program_.log()+"\n";
  }

  if(!error_str.isEmpty()){
    QMessageBox * box = new QMessageBox(this);
    box->setText(error_str);
    box->exec();
    delete box;
  }
}

void GLWidget::AutoRotate()
{
  rotx_ += auto_delta_.y();
  roty_ += auto_delta_.x();
  update();
}

void GLWidget::LoadTexture() {
  QString filename = QFileDialog::getOpenFileName(this,"Open Texture File", ".");
  QImage img;
  if(!filename.isEmpty()){
    img.load(filename);
    if(!img.isNull()){
      bindTexture(img);
    }
  }
}

void GLWidget::TogglePerspective() {
  perspective_ = !perspective_;
}

