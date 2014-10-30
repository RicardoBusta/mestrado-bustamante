#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

namespace Ui {
class MainWindow;
}

namespace Busta{
class GLWidget;
class GLWidgetScene;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  void init();

private:
  Ui::MainWindow *ui_;

  Busta::GLWidget *glwidget_;
  QMap<QString,Busta::GLWidgetScene*> scenes;

private slots:
  void setSceneCubes();
  void setScenePlanes();
};

#endif // MAINWINDOW_H
