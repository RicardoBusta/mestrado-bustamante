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

private:
  Ui::MarchingCubesSceneDialog *ui;
};

#endif // MARCHINGCUBESSCENEDIALOG_H
