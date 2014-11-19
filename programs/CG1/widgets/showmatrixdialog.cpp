#include "showmatrixdialog.h"
#include "ui_showmatrixdialog.h"

ShowMatrixDialog::ShowMatrixDialog(const Busta::Matrix4x4 &matrix, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ShowMatrixDialog)
{
  ui->setupUi(this);

  ui->label00->setText(QString::number(matrix.data(0,0)));
  ui->label10->setText(QString::number(matrix.data(1,0)));
  ui->label20->setText(QString::number(matrix.data(2,0)));
  ui->label30->setText(QString::number(matrix.data(3,0)));

  ui->label01->setText(QString::number(matrix.data(0,1)));
  ui->label11->setText(QString::number(matrix.data(1,1)));
  ui->label21->setText(QString::number(matrix.data(2,1)));
  ui->label31->setText(QString::number(matrix.data(3,1)));

  ui->label02->setText(QString::number(matrix.data(0,2)));
  ui->label12->setText(QString::number(matrix.data(1,2)));
  ui->label22->setText(QString::number(matrix.data(2,2)));
  ui->label32->setText(QString::number(matrix.data(3,2)));

  ui->label03->setText(QString::number(matrix.data(0,3)));
  ui->label13->setText(QString::number(matrix.data(1,3)));
  ui->label23->setText(QString::number(matrix.data(2,3)));
  ui->label33->setText(QString::number(matrix.data(3,3)));
}

ShowMatrixDialog::~ShowMatrixDialog()
{
  delete ui;
}
