#include "scivis.h"

#include <QDebug>

int main(int argc, char *argv[])
{
  SciVis scivis(argc, argv);

  int ret = scivis.exec();
  scivis.clean();
  qDebug() << "ret" << ret;
  return ret;
}
