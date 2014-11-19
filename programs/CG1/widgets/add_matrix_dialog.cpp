#include "add_matrix_dialog.h"
#include "ui_add_matrix_dialog.h"

AddMatrixDialog::AddMatrixDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::AddMatrixDialog)
{
  ui->setupUi(this);
}

AddMatrixDialog::~AddMatrixDialog()
{
  delete ui;
}

QString AddMatrixDialog::resulting_string() const
{
  return resulting_string_;
}
