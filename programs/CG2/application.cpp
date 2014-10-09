#include "application.h"

#include "structures/texturecontainer.h"

Application::Application(int &argc, char **argv) :
  QApplication(argc,argv)
{  
  main_window_ = new MainWindow(&scene_);
  main_window_->show();
//  opencl_loader_ = new OpenClLoader();

//  opencl_raytracing_ = new OpenClRayTracing(opencl_loader_);
}

Application::~Application()
{
  TextureContainer::instance()->Clear();
//  delete opencl_loader_;
}
