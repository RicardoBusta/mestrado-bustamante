#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

class GLWidget : public QGLWidget
{
  Q_OBJECT

public:
  explicit GLWidget(QWidget *parent = 0);
  ~GLWidget();

protected:
  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();
  void clearGL();

private:
  float rot_angle;
private slots:
  void updateAngle();
};

#endif // GLWIDGET_H
