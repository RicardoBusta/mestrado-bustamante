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

protected:
  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();


  virtual void setViewport(int w, int h);


private:
  QTimer timer_;

  Busta::GLWidgetScene *scene_;
signals:

public slots:

};

}

#endif // BUSTA_GLWIDGET_H
