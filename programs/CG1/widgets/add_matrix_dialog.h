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

  QString resulting_string() const;
private:
  Ui::AddMatrixDialog *ui;

  QString resulting_string_;
};

#endif // ADD_MATRIX_DIALOG_H
