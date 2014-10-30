#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "opengl/textures.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::init()
{
  Textures::instance()->setGlWidget(ui->centralWidget);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
  ui->centralWidget->keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
  ui->centralWidget->keyReleaseEvent(event);
}
