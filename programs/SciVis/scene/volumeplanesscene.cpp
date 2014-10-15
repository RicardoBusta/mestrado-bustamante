#include "volumeplanesscene.h"

#include <QtOpenGL>

VolumePlanesScene::VolumePlanesScene()
{
}

void VolumePlanesScene::paint()
{
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glBegin(GL_QUADS);
  glVertex3f(0,0,0);
  glVertex3f(1,0,0);
  glVertex3f(1,1,0);
  glVertex3f(0,1,0);
  glEnd();
}
