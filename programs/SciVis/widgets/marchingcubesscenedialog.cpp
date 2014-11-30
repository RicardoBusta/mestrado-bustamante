#include "marchingcubesscenedialog.h"
#include "ui_marchingcubesscenedialog.h"

MarchingCubesSceneDialog::MarchingCubesSceneDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::MarchingCubesSceneDialog)
{
  ui->setupUi(this);
}

MarchingCubesSceneDialog::~MarchingCubesSceneDialog()
{
  delete ui;
}
