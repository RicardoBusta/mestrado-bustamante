#include "space3d.h"
#include "mainwindow.h"

Space3D::Space3D(int argc, char *argv[]) :
  QApplication(argc,argv)
{
  main_window = new MainWindow();

  main_window->init();
  main_window->show();
}

Space3D::~Space3D()
{
}
