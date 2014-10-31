#include "scivis.h"

#include "busta_libs/opencl_manager/openclmanager.h"

#include <QDebug>

SciVis::SciVis(int argc, char *argv[]) :
  QApplication(argc,argv)
{
  if(!Busta::OpenCLManager::instance()->LoadLib()){
    qWarning() << "Do not have support for opencl";
    return;
  }

  w.show();
  w.init();
}

void SciVis::clean()
{
  //Busta::OpenCLManager::instance()->UnloadLibrary();
  qDebug() << "cleaning";
}
