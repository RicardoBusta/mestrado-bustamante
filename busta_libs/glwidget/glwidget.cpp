#include "glwidget.h"

#include "busta_libs/glwidget/glwidgetscene.h"

namespace Busta{

GLWidget::GLWidget(QWidget *parent) :
  QGLWidget(parent),
  scene_(NULL)
{
}

void GLWidget::initializeGL()
{
}

void GLWidget::resizeGL(int w, int h)
{
  setViewport(w,h);
}

void GLWidget::paintGL()
{
  if(NULL != scene_){
    scene_->paint();
  }
}

void GLWidget::setViewport(int w, int h)
{
  int size = qMax(w,h);
  glViewport((w-size)/2,(h-size)/2,size,size);
}

}
