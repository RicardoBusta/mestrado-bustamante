#include "raytracingthread.h"

#include <QDebug>
#include <QThread>

#include "programs/CG2/ray.h"
#include "programs/CG2/scene/scene.h"

RayTracingThread::RayTracingThread(const QRect &rect, const int &id, const float &prop_x, const float &prop_y, const float &val_x, const float &val_y, const Scene *scene, QObject *parent)
  : QObject(parent),
    rect(rect),
    prop_x(prop_x),
    prop_y(prop_y),
    val_x(val_x),
    val_y(val_y),
    scene_(scene),
    id(id),
    aborted(false),
    level_(0)
{
  image_ = QImage(rect.size(),QImage::Format_ARGB32);
  image_.fill(Qt::black);
  //  auto_update_timer = new QTimer(this);
  //  connect(auto_update_timer,SIGNAL(timeout()),this,SLOT(Step()));
  //  auto_update_timer->start(100);
  //  qDebug() << "thread created";

}

RayTracingThread::~RayTracingThread()
{
}

void RayTracingThread::Work()
{
//  qDebug() << id <<"work";
//  qDebug() << rect;
  for(int i=0;i<rect.width();i++){
    for(int j=0;j<rect.height();j++){
      if(aborted){ emit Finished(); return; };
      float x = prop_x * float(rect.x()+i) + val_x;
      float y = prop_y * float(rect.y()+j) + val_y;

      Ric::Vector vfx1 = ((1-x)*scene_->frustum[8]) + ((x)*scene_->frustum[7]);
      Ric::Vector vfx2 = ((1-x)*scene_->frustum[5]) + ((x)*scene_->frustum[6]);
      Ric::Vector vnx1 = ((1-x)*scene_->frustum[4]) + ((x)*scene_->frustum[3]);
      Ric::Vector vnx2 = ((1-x)*scene_->frustum[1]) + ((x)*scene_->frustum[2]);

            Ric::Vector far_plane = (y*vfx1)+((1-y)*vfx2);
            Ric::Vector near_plane = (y*vnx1)+((1-y)*vnx2);

            Ray ray(scene_->frustum[0],far_plane.Normalized(),far_plane.Length(),near_plane.Length(),Ric::Color(0xff000000));
            ray.calc(ray.cast(scene_),scene_,level_,true);

            image_.setPixel(i,j,ray.color().Argb());
    }
  }
  emit Finished();
}
