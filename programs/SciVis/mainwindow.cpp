#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "busta_libs/glwidget/glwidget.h"

#include "scene/volumeplanesscene.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui_(new Ui::MainWindow)
{
  ui_->setupUi(this);

  glwidget_ = new Busta::GLWidget(this);
  glwidget_->setScene(new VolumePlanesScene());

  setCentralWidget(glwidget_);
}

MainWindow::~MainWindow()
{
  delete ui_;
}
