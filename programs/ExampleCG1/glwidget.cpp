#include "glwidget.h"

#include <QMouseEvent>
#include <QWheelEvent>
#include <QTimer>
#include <QDebug>
#include <iostream>

const float kZoomTransform = 1.0f/10000.0f;
const float kRotateTransform = 0.5f;

GLWidget::GLWidget(QWidget *parent) :
  QGLWidget(parent),
  zoom_(10000),
  rotx_(0),
  roty_(0),
  rotz_(0)
{
  QTimer *timer = new QTimer(this);

  connect(timer,SIGNAL(timeout()),this,SLOT(updateGL()));
  connect(timer,SIGNAL(timeout()),this,SLOT(stepScene()));

  timer->start(1000/60);

  vertex_.push_back(GLVertex(Vector4(-1,-1,-1,1),QColor(0,0,0)));
  vertex_.push_back(GLVertex(Vector4(1,-1,-1,1),QColor(255,0,0)));
  vertex_.push_back(GLVertex(Vector4(1,1,-1,1),QColor(255,255,0)));
  vertex_.push_back(GLVertex(Vector4(-1,1,-1,1),QColor(0,255,0)));

  vertex_.push_back(GLVertex(Vector4(-1,-1,1,1),QColor(0,0,255)));
  vertex_.push_back(GLVertex(Vector4(1,-1,1,1),QColor(255,0,255)));
  vertex_.push_back(GLVertex(Vector4(1,1,1,1),QColor(255,255,255)));
  vertex_.push_back(GLVertex(Vector4(-1,1,1,1),QColor(0,255,255)));

  // back
  index_.push_back(0);
  index_.push_back(2);
  index_.push_back(1);

  index_.push_back(0);
  index_.push_back(3);
  index_.push_back(2);

  // front
  index_.push_back(4);
  index_.push_back(5);
  index_.push_back(6);

  index_.push_back(4);
  index_.push_back(6);
  index_.push_back(7);

  // top
  index_.push_back(2);
  index_.push_back(3);
  index_.push_back(7);

  index_.push_back(2);
  index_.push_back(7);
  index_.push_back(6);

  // bot
  index_.push_back(0);
  index_.push_back(1);
  index_.push_back(5);

  index_.push_back(0);
  index_.push_back(5);
  index_.push_back(4);

  // left
  index_.push_back(0);
  index_.push_back(7);
  index_.push_back(3);

  index_.push_back(0);
  index_.push_back(4);
  index_.push_back(7);

  // right
  index_.push_back(1);
  index_.push_back(2);
  index_.push_back(5);

  index_.push_back(2);
  index_.push_back(6);
  index_.push_back(5);
}

void GLWidget::initializeGL()
{
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
}

void GLWidget::resizeGL(int w, int h)
{
  float size = qMax(w,h);
  glViewport((w-size)/2,(h-size)/2,size,size);

  projection.loadIdentity();
  //===Frustum===
  projection.frustum(-0.1f,0.1f,-0.1f,0.1f,0.1f,1000.0f);
  projection.translate(0.f,0.f,-5.0f);
  //===Ortho===
//  projection.ortho(-3.0f,3.0f,-3.0f,3.0f,3.0f,-3.0f);
  glMatrixMode(GL_PROJECTION);
//  glLoadMatrixf(projection.data());
  glMatrixMode(GL_MODELVIEW);

  GLenum e;
  while(e = glGetError()){
    qDebug() << "gl error" << e;
  }
}

void GLWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  modelview.loadIdentity();

  float zoom = float(zoom_)*kZoomTransform;

  modelview.scale(zoom);
  modelview.rotateX(rotx_);
  modelview.rotateY(roty_);
  modelview.rotateZ(rotz_);

  //===Projection===
  Matrix4x4 proj = projection;
  //===Identity===
  //Matrix4x4 proj = Matrix4x4;

  glBegin(GL_TRIANGLES);

  for(int i=0;i<index_.size();i++){
    vertex(vertex_[index_[i]], proj*modelview);
  }

  glEnd();

  modelview.scale(0.5);

  glBegin(GL_TRIANGLES);
  for(int i=0;i<index_.size();i++){
    vertex(vertex_[index_[i]], proj*modelview);
  }
  glEnd();
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
    auto_delta_ = delta_*0.5;
  }else{
    auto_delta_ = QPoint(0,0);
  }

  event->accept();
}


void GLWidget::wheelEvent(QWheelEvent *event)
{
  zoom_ += event->delta();

  zoom_ = qMax( 100, qMin(50000,zoom_) );

  event->accept();
}


void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
  delta_ = event->pos()-last_click_;
  last_click_ = event->pos();
  if(event->buttons() & Qt::LeftButton){
    rotx_ += delta_.y()*kRotateTransform;
    roty_ += delta_.x()*kRotateTransform;
  }

  event->accept();
}

void GLWidget::vertex(const GLVertex &vertex, const Matrix4x4 &transform)
{
  Vector4 transformed = transform * vertex.v_;
  QColor c = vertex.c_;
  glColor3f(c.redF(),c.greenF(),c.blueF());
  glVertex3f(transformed.x(),transformed.y(),transformed.z());
}

void GLWidget::stepScene()
{
  rotx_ += auto_delta_.y()*kRotateTransform;
  roty_ += auto_delta_.x()*kRotateTransform;
}

