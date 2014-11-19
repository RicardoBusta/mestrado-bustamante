#ifndef ADD_MATRIX_DIALOG_H
#define ADD_MATRIX_DIALOG_H

#include <QDialog>

namespace Ui {
  class AddMatrixDialog;
}

class AddMatrixDialog : public QDialog
{
  Q_OBJECT

public:
  explicit AddMatrixDialog(QWidget *parent = 0);
  ~AddMatrixDialog();

private:
  Ui::AddMatrixDialog *ui;
};

#endif // ADD_MATRIX_DIALOG_H
