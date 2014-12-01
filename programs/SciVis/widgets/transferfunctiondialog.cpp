#include "transferfunctiondialog.h"
#include "ui_transferfunctiondialog.h"

TransferFunctionDialog::TransferFunctionDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::TransferFunctionDialog)
{
  ui->setupUi(this);

  transfer_function = ui->widget->tf;
}

TransferFunctionDialog::~TransferFunctionDialog()
{
  delete ui;
}
