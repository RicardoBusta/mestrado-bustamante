#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "busta_libs/glwidget/glwidget.h"

#include "scene/volumeplanesscene.h"
#include "scene/marchingcubesscene.h"
#include "loadingprogress.h"

#include <QTimer>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui_(new Ui::MainWindow)
{
  ui_->setupUi(this);

  connect(ui_->planes_button,SIGNAL(clicked()),this,SLOT(setScenePlanes()));
  connect(ui_->cubes_button,SIGNAL(clicked()),this,SLOT(setSceneCubes()));
}

MainWindow::~MainWindow()
{
  foreach(Busta::GLWidgetScene* scene,scenes){
    if(scene!=NULL){
      delete scene;
    }
  }
  scenes.clear();
  delete ui_;
}

void MainWindow::init(){
  scenes.insert("planes",new VolumePlanesScene());
  scenes.insert("cubes",new MarchingCubesScene());

  ui_->widget->setScene(NULL);

  //setCentralWidget(glwidget_);
}

#include "widgets/marchingcubesscenedialog.h"

void MainWindow::setSceneCubes()
{
  qDebug() << "Setting marching cube scene";
  MarchingCubesScene *ps = dynamic_cast<MarchingCubesScene*>(scenes["cubes"]);
  if(ps!=NULL){
    QString res = QFileDialog::getOpenFileName();
    qDebug() << "opened?";
    MarchingCubesSceneDialog dialog(this);
    dialog.exec();
    if(!res.isEmpty()){
      ps->file_name = res;
      ps->iso_value = 205;
    }
  }
  this->raise();
  ui_->widget->setScene(scenes["cubes"]);
  ui_->widget->setGeometry(ui_->widget->geometry());
}

void MainWindow::setScenePlanes()
{
  LoadingProgress *progress = new LoadingProgress(this);
  progress->setGeometry(this->rect());
  progress->show();
  progress->raise();
  qDebug() << "Setting planes scene";
  VolumePlanesScene *ps = dynamic_cast<VolumePlanesScene*>(scenes["planes"]);
  if(ps!=NULL){
    QString res = QFileDialog::getOpenFileName();
    qDebug() << "opened?";
    if(!res.isEmpty()) ps->file_name = res;
  }
  ui_->widget->setScene(scenes["planes"]);
  ui_->widget->setGeometry(ui_->widget->geometry());
  progress->hide();
}
