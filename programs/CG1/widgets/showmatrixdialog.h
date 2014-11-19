#ifndef SHOWMATRIXDIALOG_H
#define SHOWMATRIXDIALOG_H

#include <QDialog>
#include "busta_libs/common_structures/matrix4x4.h"

namespace Ui {
  class ShowMatrixDialog;
}

class ShowMatrixDialog : public QDialog
{
  Q_OBJECT

public:
  explicit ShowMatrixDialog(const Busta::Matrix4x4 &matrix,QWidget *parent = 0);
  ~ShowMatrixDialog();

private:
  Ui::ShowMatrixDialog *ui;
};

#endif // SHOWMATRIXDIALOG_H
