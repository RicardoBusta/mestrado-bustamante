#include "glwidget.h"

#include "busta_libs/glwidget/glwidgetscene.h"

#include <QMouseEvent>
#include <QDebug>

namespace Busta{

  GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent),
    scene_(NULL),
    auto_rot_speed_(0.4f)
  {
    connect(&timer_,SIGNAL(timeout()),this,SLOT(sceneStep()));
    connect(&timer_,SIGNAL(timeout()),this,SLOT(updateGL()));
    timer_.start(1000/60);
    connect(this,SIGNAL(destroyed()),this,SLOT(releaseContent()));
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

    scene_->initGL();
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

    scene_->rotx_+=auto_delta_.y()*auto_rot_speed_;
    scene_->roty_+=auto_delta_.x()*auto_rot_speed_;
    scene_->paintGL();
  }

  void GLWidget::releaseContent()
  {
    qDebug() << "releaseContent";
    if(NULL == scene_) return;
    scene_->release();
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
    if(scene_==NULL) return;

    auto_delta_ = QPoint(0,0);
    last_click_ = event->pos();

    event->accept();
  }


  void GLWidget::mouseReleaseEvent(QMouseEvent *event)
  {
    if(scene_==NULL) return;

    if(delta_.manhattanLength() > 5){
      auto_delta_ = delta_;
    }else{
      auto_delta_ = QPoint(0,0);
    }

    event->accept();
  }


  void GLWidget::wheelEvent(QWheelEvent *event)
  {
    if(scene_==NULL) return;

    qDebug() << scene_->zoom_;

    scene_->zoom_ += event->delta();

    event->accept();
  }


  void GLWidget::mouseMoveEvent(QMouseEvent *event)
  {
    if(scene_==NULL) return;

    delta_ = event->pos()-last_click_;
    last_click_ = event->pos();
    if(event->buttons() & Qt::LeftButton){
      scene_->rotx_ += delta_.y();
      scene_->roty_ += delta_.x();
    }

    event->accept();
  }

  void GLWidget::setScene(GLWidgetScene *scene)
  {
    scene_ = scene;
    if(scene_!=NULL){
      scene_->init();
    }
  }

}
