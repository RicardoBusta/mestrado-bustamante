#include "mainwindow.h"
#include "space3d.h"

int main(int argc, char *argv[])
{
  Space3D a(argc, argv);
  return a.exec();
}
