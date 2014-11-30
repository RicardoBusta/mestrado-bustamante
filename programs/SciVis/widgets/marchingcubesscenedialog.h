#ifndef MARCHINGCUBESSCENEDIALOG_H
#define MARCHINGCUBESSCENEDIALOG_H

#include <QDialog>

namespace Ui {
  class MarchingCubesSceneDialog;
}

class MarchingCubesSceneDialog : public QDialog
{
  Q_OBJECT

public:
  explicit MarchingCubesSceneDialog(QWidget *parent = 0);
  ~MarchingCubesSceneDialog();

  int size;
  int iso_value;
  QColor color;

private:
  Ui::MarchingCubesSceneDialog *ui;

private slots:
  void setIsoValue(QString value);
  void setSize(QString value);
  void setColor();
};

#endif // MARCHINGCUBESSCENEDIALOG_H
