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

  void vertex(const GLVertex &vertex);
  void normal(const GLVertex &v1, const GLVertex &v2, const GLVertex &v3);
  QColor phong(const GLVertex &vertex);
  void loadTransform(const Matrix4x4 *loadTransform);

  // Scene
  QVector<GLVertex> vertex_;
  QVector<int> index_;
  Matrix4x4 view;
  Matrix4x4 model;
  Matrix4x4 projection;

  Vector4 current_normal_;
  Matrix4x4 current_mvp_;
  Vector4 current_light_position_;

private slots:
  void stepScene();
};

#endif // GLWIDGET_H
