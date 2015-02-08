#include "aavmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  AAVMainWindow w;
  w.show();

  return a.exec();
}
