#include "mainwindow.h"
#include <QApplication>

#include "matrix4x4.h"
#include "vector4.h"

#include <iostream>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  return a.exec();
}
