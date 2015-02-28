#include "transferfunctiondialog.h"
#include "ui_transferfunctiondialog.h"

TransferFunctionDialog::TransferFunctionDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::TransferFunctionDialog)
{
  ui->setupUi(this);

  transfer_function = ui->widget->tf;

  connect(this,SIGNAL(accepted()),this,SLOT(updateTF()));
  connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(clearTF()));
}

TransferFunctionDialog::~TransferFunctionDialog()
{
  delete ui;
}

void TransferFunctionDialog::updateTF()
{
  transfer_function = ui->widget->tf;
}

void TransferFunctionDialog::clearTF()
{
  ui->widget->tf.clear();
  transfer_function.clear();
  ui->widget->update();
}
