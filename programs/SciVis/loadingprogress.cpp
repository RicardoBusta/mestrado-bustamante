#include "loadingprogress.h"
#include "ui_loadingprogress.h"

LoadingProgress::LoadingProgress(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::LoadingProgress)
{
  ui->setupUi(this);
}

LoadingProgress::~LoadingProgress()
{
  delete ui;
}
