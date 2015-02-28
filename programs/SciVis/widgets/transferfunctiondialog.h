#ifndef TRANSFERFUNCTIONDIALOG_H
#define TRANSFERFUNCTIONDIALOG_H

#include <QDialog>
#include "algorithm/transferfunction.h"

namespace Ui {
class TransferFunctionDialog;
}

class TransferFunctionDialog : public QDialog
{
  Q_OBJECT

public:
  explicit TransferFunctionDialog(QWidget *parent = 0);
  ~TransferFunctionDialog();

  TransferFunction transfer_function;
private:
  Ui::TransferFunctionDialog *ui;
private slots:
  void updateTF();
  void clearTF();
};

#endif // TRANSFERFUNCTIONDIALOG_H
