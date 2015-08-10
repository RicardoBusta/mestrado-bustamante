#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "model.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;

  ModelMap models_;

 private slots:
  void ToggleHideCurrentModel();
  void UpdateModels();
  void LoadObjModel();
  void LoadVsh();
  void LoadFsh();
  void CompileShaders();
};

#endif  // MAINWINDOW_H
