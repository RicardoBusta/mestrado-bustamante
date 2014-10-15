#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include "programs/SciVis/mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  //GLWidget
}

MainWindow::~MainWindow()
{
  delete ui;
}
