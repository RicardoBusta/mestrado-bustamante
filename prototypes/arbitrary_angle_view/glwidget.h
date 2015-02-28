#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

class AAVGLWidget : public QGLWidget
{
  Q_OBJECT

public:
  explicit AAVGLWidget(QWidget *parent = 0);
  ~AAVGLWidget();

protected:
  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();
  void clearGL();

private:
  float rot_angle_x;
  float rot_angle_y;

  float fov_angle;

  int slices_num;

  GLuint framebuffer;
  GLuint render_texture;
  GLuint depth_buffer;
private slots:
  void updateXRotation(int xr);
  void updateYRotation(int yr);
  void updateFoVAngle(int angle);
  void updateSlices(int slices);
};

#endif // GLWIDGET_H
