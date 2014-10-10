#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>

#include "widgets/mainwindow.h"
#include "scene/scene.h"
#include "openclloader.h"
#include "openclraytracing.h"

class Application : public QApplication
{
  Q_OBJECT
public:
  explicit Application(int &argc, char **argv);
  ~Application();

private:
  Scene scene_;
  MainWindow *main_window_;
//  OpenClLoader *opencl_loader_;
//  OpenClRayTracing *opencl_raytracing_;
signals:

public slots:

};

#endif // APPLICATION_H
