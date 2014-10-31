#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "busta_libs/glwidget/glwidget.h"

#include "scene/volumeplanesscene.h"
#include "scene/marchingcubesscene.h"

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
  glwidget_ = new Busta::GLWidget(this);

  scenes.insert("planes",new VolumePlanesScene());
  scenes.insert("cubes",new MarchingCubesScene());

  glwidget_->setScene(NULL);

  ui_->glwidget_container->addWidget(glwidget_);

  //setCentralWidget(glwidget_);
}

void MainWindow::setSceneCubes()
{
  glwidget_->setScene(scenes["cubes"]);
}

void MainWindow::setScenePlanes()
{
  glwidget_->setScene(scenes["planes"]);
}
