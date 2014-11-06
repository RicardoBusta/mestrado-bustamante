#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

#include "matrix4x4.h"
#include "vector4.h"
#include "glvertex.h"

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

private:
  QPoint last_click_;
  QPoint delta_;
  QPoint auto_delta_;

  int zoom_;
  float rotx_, roty_, rotz_;

  void vertex(const GLVertex &vertex, const Matrix4x4 &transform);

  // Scene
  QVector<GLVertex> vertex_;
  QVector<int> index_;
  Matrix4x4 modelview;
  Matrix4x4 projection;

private slots:
  void stepScene();
};

#endif // GLWIDGET_H
