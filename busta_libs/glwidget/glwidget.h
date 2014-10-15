#ifndef BUSTA_GLWIDGET_H
#define BUSTA_GLWIDGET_H

#include <QGLWidget>
#include <QTimer>

namespace Busta{

class GLWidgetScene;

class GLWidget : public QGLWidget
{
  Q_OBJECT
public:
  explicit GLWidget(QWidget *parent = 0);
  virtual ~GLWidget();

  void setScene(GLWidgetScene *scene);
protected:
  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();


  virtual void setViewport(int w, int h);

  void sceneStep();

  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void wheelEvent(QWheelEvent *event);
  void mouseMoveEvent(QMouseEvent *event);

private:
  QTimer timer_;

  Busta::GLWidgetScene *scene_;
signals:

public slots:

};

}

#endif // BUSTA_GLWIDGET_H
