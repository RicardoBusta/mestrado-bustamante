#include "cgapplication.h"

#include "widgets/mainwindow.h"

#include <QTime>

CGApplication::CGApplication(int argc, char *argv[]):
  QApplication(argc,argv)
{
  main_window_ = new MainWindow();
  main_window_->init();
  main_window_->show();
}

CGApplication::~CGApplication()
{
  delete main_window_;
}

MainWindow *CGApplication::getMainWindow()
{
  return main_window_;
}
