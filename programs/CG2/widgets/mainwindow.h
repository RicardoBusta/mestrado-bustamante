#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class GLWidget;
class OuterViewWidget;
class RayTracingWidget;
class Scene;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT
private:
  Ui::MainWindow *ui_;
public:
  explicit MainWindow(Scene *scene, QWidget *parent = 0);
  ~MainWindow();

  Scene *scene_;

  GLWidget *gl_widget_;
  OuterViewWidget *outer_view_widget_;
  RayTracingWidget *ray_tracing_widget_;

  void resizeEvent(QResizeEvent *event);

  void mouseMoveEvent(QMouseEvent *e);
  void mousePressEvent(QMouseEvent *e);
  void mouseReleaseEvent(QMouseEvent *e);

public slots:
  void SceneChanged();

  void SetFov(const int value);
  void SetNear(const int value);
  void SetFar(const int value);
  void SetLight(const bool value);
  void SetTrackRay(const bool value);

  void LoadScene(int);

  void FinalRender();

};

#endif // MAINWINDOW_H
