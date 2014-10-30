#include "glwidget.h"

#include <QDebug>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QTimer>

const float kRotToAngle = 0.1f;
const float kDeltaToZoom = 0.001f;
const float kAspect = 4.0f/3.0f;

GLWidget::GLWidget(QWidget *parent) :
  QGLWidget(parent)
{
  zoom_ = 1.0f;

  QTimer *timer = new QTimer(this);
  timer->start(1000/60);

  connect(timer,SIGNAL(timeout()),this,SLOT(sceneStep()));
}

void GLWidget::initializeGL()
{
  scene.init();

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);

  glShadeModel(GL_SMOOTH);
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable( GL_BLEND );

  glEnable(GL_TEXTURE_2D);
}

void GLWidget::resizeGL(int w, int h)
{
  float aspect = float(w)/float(h);

  int xi = 0;
  int yi = 0;
  int wi = w;
  int hi = h;

  if(aspect > kAspect){
    wi = float(h)*kAspect;
    xi = float(w-wi)/2.0f;
  }else if(aspect < kAspect){
    hi = float(w)/kAspect;
    yi = float(h-hi)/2.0f;
  }

//  glViewport(0,0,w,h);
//  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glViewport(xi,yi,wi,hi);

//  int size = qMax(w,h);
//  glViewport((w-size)/2.0,(h-size)/2.0,size,size);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //  glOrtho(-1,1,-1,1,-50,50);
  glFrustum(-.04,.04,-.03,.03,0.1,100000);
  //glTranslatef(0,0,0);

  glMatrixMode(GL_MODELVIEW);
}

void GLWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  glTranslatef(0,0,-step_back_);
  glScalef(zoom_,zoom_,zoom_);
  glRotatef(rot_.y(),1,0,0);
  glRotatef(rot_.x(),0,1,0);

  scene.draw();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
  auto_delta_ = QPoint(0,0);
  last_click_ = event->pos();

  event->accept();
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
  if(delta_.manhattanLength() > 5){
    auto_delta_ = delta_*kRotToAngle;
  }else{
    auto_delta_ = QPoint(0,0);
  }

  event->accept();
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
  zoom_ += float(event->delta()) * kDeltaToZoom * zoom_;

  event->accept();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
  delta_ = event->pos()-last_click_;
  last_click_ = event->pos();
  if(event->buttons() & Qt::LeftButton){
    rot_ += delta_;
  }

  event->accept();
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
  switch(event->key()){
  case Qt::Key_Left:
    scene.current_page--;
    zoom_ = 1;
    scene.camera_timer = 0;
    break;
  case Qt::Key_Right:
  case Qt::Key_Enter:
  case Qt::Key_Space:
    scene.current_page++;
    zoom_ = 1;
    scene.camera_timer = 0;
    break;
  }
}

void GLWidget::keyReleaseEvent(QKeyEvent *event)
{

}

void GLWidget::sceneStep()
{
  rot_+=auto_delta_;

  scene.step();

  step_back_ = scene.zoom;

  updateGL();
}
