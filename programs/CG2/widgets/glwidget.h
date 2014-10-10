#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

class Scene;

namespace Ric{
class Color;
class Vector;
}

class GLWidget : public QGLWidget
{
  Q_OBJECT
public:
  explicit GLWidget(Scene *scene, QWidget *parent = 0);

  void paintGL();
  void initializeGL();
  void resizeGL(int w, int h);
  int heightForWidth(int w) const;

  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void wheelEvent(QWheelEvent *event);

  void Frustum( const float &fov, const float &ratio, const float &n, const float &f );

  Scene *scene_;

  QPoint last_pos_;
signals:
  void MouseMoved(QMouseEvent*);
  void MousePressed(QMouseEvent*);
  void MouseReleased(QMouseEvent*);
  void Wheel(QWheelEvent*);
public slots:

};

#endif // GLWIDGET_H
