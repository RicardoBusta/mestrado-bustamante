#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

#include <QGLShaderProgram>
#include "programs/CG1/opengl/scene.h"

class GLWidget : public QGLWidget
{
  Q_OBJECT
public:
  explicit GLWidget(QWidget *parent = 0);
  virtual ~GLWidget();

  QTimer *timer_;

protected:
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

  QGLShaderProgram shader_program_;
signals:

public slots:
  void sceneStep();
};

#endif // GLWIDGET_H
