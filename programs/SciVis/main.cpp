#include "scivis.h"

int main(int argc, char *argv[])
{
  SciVis a(argc, argv);

  int ret = a.exec();
  a.clean();
  return ret;
}
