#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "busta_libs/glwidget/glwidget.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui_(new Ui::MainWindow)
{
  ui_->setupUi(this);

  glwidget_ = new Busta::GLWidget(this);

  setCentralWidget(glwidget_);
}

MainWindow::~MainWindow()
{
  delete ui_;
}
