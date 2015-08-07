#include "glwidget.h"

#include <QDebug>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QTimer>
#include <QFileDialog>
#include <QImage>

const float kRotDeltaToAngle = 0.5f;
const float kAutoDeltaToAngle = 0.1f;
const float kZoomDeltaToAngle = 0.001f;

GLWidget::GLWidget(QWidget *parent)
  : QGLWidget(parent),
    models_(NULL),
    zoom_(0.5),
    rotx_(0),
    roty_(0),
    timer_(new QTimer(this)){
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
  glClearColor(0.0f,0.0f,0.0f,1.0f);
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

  QImage img(QSize(16,16),QImage::Format_ARGB32);
  img.fill(0xffff9900);
  for(int i=0;i<16;i++){
    img.setPixel(i,0,0xff000000);
    img.setPixel(0,i,0xff000000);
    img.setPixel(i,i,0xffffffff);
    img.setPixel(i,15,0xffffffff);
    img.setPixel(15,i,0xffffffff);
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
  glOrtho(-1*ratio,1*ratio,-1,1,-100,100);
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

