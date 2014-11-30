#include "marchingcubesscenedialog.h"
#include "ui_marchingcubesscenedialog.h"

#include <QDebug>
#include <QColorDialog>

MarchingCubesSceneDialog::MarchingCubesSceneDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::MarchingCubesSceneDialog)
{
  ui->setupUi(this);

  connect(ui->iso_line,SIGNAL(textChanged(QString)),this,SLOT(setIsoValue(QString)));
  connect(ui->size_line,SIGNAL(textChanged(QString)),this,SLOT(setSize(QString)));
  connect(ui->color_button,SIGNAL(clicked()),this,SLOT(setColor()));


  ui->size_line->setText("50");
  ui->iso_line->setText("200");
}

MarchingCubesSceneDialog::~MarchingCubesSceneDialog()
{
  delete ui;
}

void MarchingCubesSceneDialog::setIsoValue(QString value)
{
  qDebug() << "Setting iso value" << value;
  iso_value = value.toInt();
}

void MarchingCubesSceneDialog::setSize(QString value)
{
  qDebug() << "Setting size value" << value;
  size = value.toInt();
}

void MarchingCubesSceneDialog::setColor()
{
  color = QColorDialog::getColor();
  ui->color_button->setStyleSheet(QString("background-color: %1;").arg(color.name()));
}
