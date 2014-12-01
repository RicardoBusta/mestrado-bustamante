#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "busta_libs/glwidget/glwidget.h"

#include "scene/volumeplanesscene.h"
#include "scene/marchingcubesscene.h"
#include "loadingprogress.h"

#include "widgets/marchingcubesscenedialog.h"
#include "widgets/transferfunctiondialog.h"

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

void MainWindow::setSceneCubes()
{
  qDebug() << "Setting marching cube scene";
  MarchingCubesScene *ps = dynamic_cast<MarchingCubesScene*>(scenes["cubes"]);
  if(ps==NULL) return;

  QString res = QFileDialog::getOpenFileName();
  if(res.isEmpty()) return;

  MarchingCubesSceneDialog dialog(this);
  int result = dialog.exec();
  if(result == QDialog::Rejected) return;

  ps->file_name = res;
  ps->iso_value = dialog.iso_value;
  ps->cube_size = dialog.size;
  ps->color = dialog.color;

  LoadingProgress *progress = new LoadingProgress(this);
  progress->setGeometry(this->rect());
  progress->show();
  progress->raise();

  this->raise();
  ui_->widget->setScene(scenes["cubes"]);
  ui_->widget->setGeometry(ui_->widget->geometry());

  delete progress;
}

void MainWindow::setScenePlanes()
{
  qDebug() << "Setting planes scene";
  VolumePlanesScene *ps = dynamic_cast<VolumePlanesScene*>(scenes["planes"]);
  if(ps==NULL) return;

  QString res = QFileDialog::getOpenFileName();
  if(res.isEmpty()) return;

  TransferFunctionDialog dialog(this);
  int result = dialog.exec();
  if(result == QDialog::Rejected) return;

  ps->file_name = res;
  ps->tf = dialog.transfer_function;

  LoadingProgress *progress = new LoadingProgress(this);
  progress->setGeometry(this->rect());
  progress->show();
  progress->raise();

  this->raise();
  ui_->widget->setScene(scenes["planes"]);
  ui_->widget->setGeometry(ui_->widget->geometry());

  delete progress;
}
