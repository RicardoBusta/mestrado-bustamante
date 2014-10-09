#ifndef OUTERVIEWWIDGET_H
#define OUTERVIEWWIDGET_H

#include <QGLWidget>

#include "structures.h"

class Scene;

class OuterViewWidget : public QGLWidget
{
  Q_OBJECT
public:
  explicit OuterViewWidget(Scene *scene_, QWidget *parent = 0);

  void paintGL();
  void initializeGL();
  void resizeGL(int w, int h);
    int heightForWidth(int w) const;

  void vertex3f(Ric::Vector v);
  void normal3f(Ric::Vector v);
  void color3f(Ric::Color c);

  void frustum(float fov, float ratio, float n, float f);

  void drawFrustum();

  Scene *scene_;

  float rotx, roty, distz;

  QPoint last_pos;

  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void wheelEvent(QWheelEvent *event);
signals:
  void Changed();
public slots:

};

#endif // OUTERVIEWWIDGET_H
