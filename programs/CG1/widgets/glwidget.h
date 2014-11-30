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

  void setShaders(const QString &vert_shader, const QString &frag_shader);
  void releaseShader();

protected:
  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();
  void popUpLogMessage(QString msg);

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

  void exportFrameBuffer();
};

#endif // GLWIDGET_H
