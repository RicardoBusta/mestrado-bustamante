#include "raytracingwidget.h"

#include <QPainter>
#include <QResizeEvent>
#include <QWheelEvent>
#include <QTimer>

#include "ray.h"
#include "scene/scene.h"
#include "constants.h"

RayTracingWidget::RayTracingWidget(Scene *scene_, QWidget *parent):
  QWidget(parent),
  scene_(scene_),
  moving_(false),
  auto_update_timer(new QTimer(this)),
  fast_render_only(true),
  recursion_level_(0)
{
  if(image_.isNull()){
    image_ = QImage(kImageMovingSize,kImageMovingSize,QImage::Format_ARGB32);
  }
  if(quick_image_.isNull()){
    quick_image_ = QImage(kImageMovingSize,kImageMovingSize,QImage::Format_ARGB32);
  }
  connect(auto_update_timer, SIGNAL(timeout()),this,SLOT(UpdateStep()));
}

RayTracingWidget::~RayTracingWidget()
{
  delete auto_update_timer;
}

void RayTracingWidget::resizeEvent(QResizeEvent *event)
{
  Q_UNUSED(event);
}

void RayTracingWidget::paintEvent(QPaintEvent *event)
{
  Q_UNUSED(event);
  QPainter painter(this);
  int size = qMin(width(),height());
  QRect img_rect = QRect((width()-size)/2,(height()-size)/2,size,size);
//  if(moving_){
//    painter.drawImage(img_rect,quick_image_.scaled(img_rect.size()).mirrored(false,true));
//  }else{
    painter.drawImage(img_rect,image_.scaled(img_rect.size()).mirrored(false,true));
//  }
}

int RayTracingWidget::heightForWidth(int w) const
{
  return w;
}

void RayTracingWidget::mousePressEvent(QMouseEvent *event)
{
  auto_update_timer->stop();
  last_pos = event->pos();
  SetMoving(true);
//  image_.scaledToHeight(s);
//  if(!image_.isNull() && image_.size() != QSize(s,s)){
//    image_ = /*QImage(scene.selected_image_size,scene.selected_image_size,QImage::Format_ARGB32);*/image_.scaled(s,s);
//  }
}

void RayTracingWidget::mouseReleaseEvent(QMouseEvent *event)
{
  Q_UNUSED(event);
  SetMoving(false);
  emit Changed();
}

void RayTracingWidget::mouseMoveEvent(QMouseEvent *event)
{
  QPoint delta = event->pos()-last_pos;
  last_pos = event->pos();
  scene_->rotx += float(delta.y())/2.0;
  scene_->roty += float(delta.x())/2.0;
  //updateFast();
  emit Changed();
}

void RayTracingWidget::wheelEvent(QWheelEvent *event)
{
  scene_->distz+=float(event->delta())/100.0f;
  emit Changed();
}

void RayTracingWidget::TryUpdate()
{
//  if(auto_update_timer->isActive()) return;

//  qDebug() << image_.size();
  if(moving_ || fast_render_only){
    if(auto_update_timer->isActive()){
      auto_update_timer->stop();
    }
    UpdateFast();
//    qDebug() << "gottago fast";
  }else{
    auto_update_i = 0;
    auto_update_j = 0;
//    int s = moving_?kImageMovingSize:scene.selected_image_size;
//    if(!image_.isNull()){
//    QImage scaled_image = image_.scaled(s,s);
//    image_ = QImage(s,s,QImage::Format_ARGB32);
//    image_.swap(scaled_image);
//    }
    //image_ = scaled_image;
//    image_ = image_.scaledToHeight(s);
//    if(image_.isNull()){
//      image_ = QImage(scene.selected_image_size,scene.selected_image_size,QImage::Format_ARGB32);
//    }else if(image_.size() != QSize(s,s)){
//      image_ = /*QImage(scene.selected_image_size,scene.selected_image_size,QImage::Format_ARGB32);*/image_.scaled(s,s);
//    }
    prop_x = (1.0f/float(image_.width()-1));
    prop_y = (1.0f/float(image_.height()-1));
    auto_update_steps = 1000;
    if(!auto_update_timer->isActive()){
      auto_update_timer->start(10);
    }
  }
}

void RayTracingWidget::UpdateStep()
{
//  if(!scene.valid_) return;

  if(moving_ || fast_render_only) return;
  for(int i=0;i<auto_update_steps;i++){
    if(auto_update_i>=image_.width()){
      auto_update_i=0; auto_update_j++;
      if(auto_update_j>=image_.height()){
        auto_update_j=0;
        auto_update_timer->stop();
      }
    }

    if( scene_->track_one_ray && (auto_update_i==scene_->specialx || auto_update_j==scene_->specialy) && !(auto_update_i==scene_->specialx && auto_update_j==scene_->specialy)){
      image_.setPixel(auto_update_i,auto_update_j,0xffff0000);
      auto_update_i++;
      continue;
    }

    float x = prop_x * float(auto_update_i);
    float y = prop_y * float(auto_update_j);

    Ric::Vector vfx1 = ((1-x)*scene_->frustum[8]) + ((x)*scene_->frustum[7]);
    Ric::Vector vfx2 = ((1-x)*scene_->frustum[5]) + ((x)*scene_->frustum[6]);
    Ric::Vector vnx1 = ((1-x)*scene_->frustum[4]) + ((x)*scene_->frustum[3]);
    Ric::Vector vnx2 = ((1-x)*scene_->frustum[1]) + ((x)*scene_->frustum[2]);

    Ric::Vector far_plane = (y*vfx1)+((1-y)*vfx2);
    Ric::Vector near_plane = (y*vnx1)+((1-y)*vnx2);

    Ray ray(scene_->frustum[0],far_plane.Normalized(),far_plane.Length(),near_plane.Length(),Ric::Color(0xff000000));
    ray.calc(ray.cast(scene_),scene_,recursion_level_,scene_->calculate_advanced_light);

    image_.setPixel(auto_update_i,auto_update_j,ray.color().Argb());

    auto_update_i++;
  }

  repaint();
}

void RayTracingWidget::RayTracingLevel(int l)
{
  recursion_level_ = l;
}

void RayTracingWidget::SetMoving(bool moving)
{
  moving_ = moving;
//  int s = moving_?kImageMovingSize:scene.selected_image_size;
}

void RayTracingWidget::MouseMoved(QMouseEvent *e)
{
  mouseMoveEvent(e);
}

void RayTracingWidget::MousePressed(QMouseEvent *e)
{
  mousePressEvent(e);
}

void RayTracingWidget::MouseReleased(QMouseEvent *e)
{
  mouseReleaseEvent(e);
}

void RayTracingWidget::Wheel(QWheelEvent *e)
{
  wheelEvent(e);
}

void RayTracingWidget::UpdateFast()
{
//  if(auto_update_timer->isActive()) return;
//  if(image_.width()>kImageMovingSize){
//    image_ = image_.scaled(kImageMovingSize,kImageMovingSize);
//  }
  prop_x = (1.0f/float(image_.width()-1));
  prop_y = (1.0f/float(image_.height()-1));

//  if(!scene.valid_) return;

  for(int i=0;i<image_.width();i++){
    float x = prop_x * float(i);
    Ric::Vector vfx1 = ((1-x)*scene_->frustum[8]) + ((x)*scene_->frustum[7]);
    Ric::Vector vfx2 = ((1-x)*scene_->frustum[5]) + ((x)*scene_->frustum[6]);
    Ric::Vector vnx1 = ((1-x)*scene_->frustum[4]) + ((x)*scene_->frustum[3]);
    Ric::Vector vnx2 = ((1-x)*scene_->frustum[1]) + ((x)*scene_->frustum[2]);
    for(int j=0;j<image_.height();j++){
      if( scene_->track_one_ray && (i==scene_->specialx || j==scene_->specialy) && !(i==scene_->specialx && j==scene_->specialy)){
        image_.setPixel(i,j,0xffff0000);
        continue;
      }

      float y = prop_y * float(j);
      Ric::Vector far_plane = (y*vfx1)+((1-y)*vfx2);
      Ric::Vector near_plane = (y*vnx1)+((1-y)*vnx2);

      Ray ray(scene_->frustum[0],far_plane.Normalized(),far_plane.Length(),near_plane.Length(),Ric::Color(0xff000000));
      const TriangleFace *f = ray.cast(scene_);
      ray.calc(f,scene_,0,false);

      image_.setPixel(i,j,ray.color().Argb());
    }
  }

  repaint();
}

void RayTracingWidget::ToggleFastRenderOnly(bool value)
{
  fast_render_only = value;
  if(value){
    UpdateFast();
  }else{
    TryUpdate();
  }
}

//void RayTracingWidget::SelectImageSize(int index)
//{
////  qDebug() << "select";
//  switch(index){
//  case 0:
//    scene.selected_image_size = 50;
//    break;
//  case 1:
//    scene.selected_image_size = 100;
//    break;
//  case 2:
//    scene.selected_image_size = 200;
//    break;
//  case 3:
//    scene.selected_image_size = 400;
//    break;
//  case 4:
//    scene.selected_image_size = 800;
//    break;
//  default:
//    scene.selected_image_size = 50;
//    break;
//  }
//  scene.specialx = scene.selected_image_size/2;
//  scene.specialy = scene.selected_image_size/2;
//  TryUpdate();
//}
