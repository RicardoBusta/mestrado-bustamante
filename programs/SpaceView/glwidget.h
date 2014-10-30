#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

#include "scene.h"

#include "object.h"

class GLWidget : public QGLWidget
{
  Q_OBJECT
public:
  explicit GLWidget(QWidget *parent = 0);

  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();

  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void wheelEvent(QWheelEvent *event);
  void mouseMoveEvent(QMouseEvent *event);

  void keyPressEvent(QKeyEvent *event);
  void keyReleaseEvent(QKeyEvent *event);

private:
  QPoint last_click_;
  QPoint delta_;
  QPoint auto_delta_;

  float zoom_;

  float step_back_;

  QPointF rot_;

  Scene scene;
private slots:
  void sceneStep();
};

#endif // GLWIDGET_H
