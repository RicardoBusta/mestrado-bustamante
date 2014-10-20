#include "scivis.h"

int main(int argc, char *argv[])
{
  SciVis scivis(argc, argv);

  int ret = scivis.exec();
  scivis.clean();
  return ret;
}
