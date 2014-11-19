#ifndef ADD_MATRIX_DIALOG_H
#define ADD_MATRIX_DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QDoubleSpinBox>

namespace Ui {
  class AddMatrixDialog;
}

typedef QPair<QLabel*,QDoubleSpinBox*> MatrixParameterWidget;

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

  QVector< MatrixParameterWidget > widgets;

  void setParameters(const QVector<QString> &params);


private slots:
  void build_string();
  void setParameters(QString type);
};

#endif // ADD_MATRIX_DIALOG_H
