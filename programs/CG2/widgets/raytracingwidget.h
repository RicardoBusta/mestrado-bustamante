#ifndef RAY_TRACING_WIDGET_H
#define RAY_TRACING_WIDGET_H

#include <QWidget>

class Scene;

class RayTracingWidget:public QWidget
{
  Q_OBJECT
public:
  explicit RayTracingWidget(Scene *scene_, QWidget *parent=0);
  ~RayTracingWidget();

  QImage image_;
  QImage quick_image_;

  Scene *scene_;

  bool moving_;

  void resizeEvent(QResizeEvent *event);
  void paintEvent(QPaintEvent *event);
    int heightForWidth(int w) const;

  QPoint last_pos;

  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void wheelEvent(QWheelEvent *event);

  //int selected_image_size;

  QTimer *auto_update_timer;
  int auto_update_i;
  int auto_update_j;
  int auto_update_steps;
  float prop_x;
  float prop_y;

  bool fast_render_only;

  int recursion_level_;

signals:
  void Changed();
public slots:
  void TryUpdate();
  void UpdateFast();
  void ToggleFastRenderOnly(bool value);
//  void SelectImageSize(int index);
  void SetMoving(bool moving);

  void MouseMoved(QMouseEvent *e);
  void MousePressed(QMouseEvent *e);
  void MouseReleased(QMouseEvent *e);
  void Wheel(QWheelEvent *e);
private slots:
  void UpdateStep();
  void RayTracingLevel(int);
};

#endif // RAY_TRACING_WIDGET_H
