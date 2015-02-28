#include "aavmainwindow.h"
#include "ui_aavmainwindow.h"

#include "glwidget.h"

AAVMainWindow::AAVMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::AAVMainWindow)
{
  ui->setupUi(this);

  connect(ui->roty_horizontalSlider,SIGNAL(valueChanged(int)),ui->glwidget,SLOT(updateXRotation(int)));
  connect(ui->fov_horizontalSlider,SIGNAL(valueChanged(int)),ui->glwidget,SLOT(updateFoVAngle(int)));
  connect(ui->slices_horizontalSlider,SIGNAL(valueChanged(int)),ui->glwidget,SLOT(updateSlices(int)));
}

AAVMainWindow::~AAVMainWindow()
{
  delete ui;
}
