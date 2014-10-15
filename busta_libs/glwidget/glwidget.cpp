#include "glwidget.h"

#include "busta_libs/glwidget/glwidgetscene.h"

namespace Busta{

GLWidget::GLWidget(QWidget *parent) :
  QGLWidget(parent),
  scene_(NULL)
{
}

GLWidget::~GLWidget()
{
  if(scene_!=NULL){
    delete scene_;
  }
}

void GLWidget::initializeGL()
{
  if(NULL == scene_) return;

  scene_->init();
}

void GLWidget::resizeGL(int w, int h)
{
  if(NULL == scene_) return;

  setViewport(w,h);
  scene_->projection();
}

void GLWidget::paintGL()
{
  if(NULL == scene_) return;

  scene_->paint();
}

void GLWidget::setViewport(int w, int h)
{
  int size = qMax(w,h);
  glViewport((w-size)/2,(h-size)/2,size,size);
}

void GLWidget::sceneStep()
{

}

void GLWidget::mousePressEvent(QMouseEvent *event)
{

}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{

}

void GLWidget::wheelEvent(QWheelEvent *event)
{

}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{

}

void GLWidget::setScene(GLWidgetScene *scene)
{
  scene_ = scene;
}

}
