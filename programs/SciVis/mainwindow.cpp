#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "busta_libs/glwidget/glwidget.h"

#include "scene/volumeplanesscene.h"
#include "scene/marchingcubesscene.h"

#include <QTimer>

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
  ui_->widget->setScene(scenes["cubes"]);
}

void MainWindow::setScenePlanes()
{
  ui_->widget->setScene(scenes["planes"]);
  ui_->widget->setGeometry(ui_->widget->geometry());
}
