#include "raytracingresultviewerwidget.h"
#include "ui_raytracingresultviewerwidget.h"

#include "structures.h"
#include "scene/scene.h"
#include "ray.h"
#include "raytracingthread.h"

#include <QThread>
#include <QPainter>

const int kThreadCount = QThread::idealThreadCount();

RayTracingResultViewerWidget::RayTracingResultViewerWidget(const Scene *scene, const QSize &img_size, const int &level, QWidget *parent)
  : QDialog(parent),
    ui(new Ui::RayTracingResultViewerWidget),
    scene_(scene),
    auto_update_steps(1000),
    level_(level)
{
  ui->setupUi(this);

  image_ = QImage(img_size,QImage::Format_ARGB32);
  image_.fill(Qt::gray);
  ui->label->setPixmap(QPixmap::fromImage(image_.mirrored(false,true)));

  float size = qMin(image_.width(),image_.height());

  float val_x = (float(image_.width())/size);
  float val_y = (float(image_.height())/size);
  float prop_x = ( val_x /float(image_.width()-1));
  float prop_y = ( val_y /float(image_.height()-1));
  val_x = (1.0-val_x)/2.0;
  val_y = (1.0-val_y)/2.0;


  thread.resize(kThreadCount);
  rtt.resize(kThreadCount);

  for(int i=0;i<kThreadCount;i++){
    thread[i] = new QThread();
    rtt[i] = new RayTracingThread(QRect(i*(image_.width()/kThreadCount),0,(image_.width()/kThreadCount),image_.height()),i,prop_x,prop_y,val_x,val_y,scene_);
    rtt[i]->level_ = this->level_;
    rtt[i]->moveToThread(thread[i]);
//    connect(thread[i],SIGNAL(finished()),rtt[i],SLOT(deleteLater()));
    connect(this,SIGNAL(StartWork()),rtt[i],SLOT(Work()));
    thread[i]->start();
  }

  //UpdateImage();

//  connect(rtt[0],SIGNAL(Finished()),thread[0],SLOT(deleteLater()));
//  connect(this,SIGNAL(finished(int)),thread[0],SLOT(quit()));

  emit StartWork();
//  connect(this,SIGNAL(finished(int)),thread[0],SLOT(quit()));
//  connect(thread1,SIGNAL(finished()),rtt[0],SLOT(deleteLater()));
//    connect(rtt[0],SIGNAL(PixelColor(int,int,uint)),this,SLOT(UpdateImage(int,int,uint)));

  connect(&auto_update_timer,SIGNAL(timeout()),this,SLOT(UpdateImage()));

  connect(this,SIGNAL(finished(int)),this,SLOT(CancelExecution()));


  auto_update_timer.start(10);
  this->showMaximized();
}

RayTracingResultViewerWidget::~RayTracingResultViewerWidget()
{
//  for(int i=0;i<kThreadCount;i++){
//    rtt[i]->aborted=true;
//  }
//  for(int i=0;i<kThreadCount;i++){
//    thread[i]->quit();
//    thread[i]->wait();
//  }
  delete ui;
}

void RayTracingResultViewerWidget::UpdateImage()
{
  //  qDebug() << "Hm" << x << y << QColor(rgb);
//  image_.setPixel(x,y,rgb);
  QPainter painter(&image_);
  for(int i=0;i<rtt.size();i++){
    QImage img = rtt[i]->image_;
    QRect rect = rtt[i]->rect;
    painter.drawImage(rect,img);
  }
  painter.end();
  ui->label->setPixmap(QPixmap::fromImage(image_.mirrored(false,true)));
}

void RayTracingResultViewerWidget::CancelExecution()
{
  for(int i=0;i<thread.size();i++){
    rtt[i]->aborted = true;
    thread[i]->terminate();

    while(!thread[i]->isFinished()){}

    if(!thread[i]->isRunning()){
      qDebug() << "thread" << i << "stopped";
    }

    rtt[i]->deleteLater();
    thread[i]->deleteLater();
  }
}
