#include "volumeplanesscene.h"

#include <QtOpenGL>
#include <QDebug>

#include "algorithm/marchingcubes.h"

const float kZoomFactor = 0.001;

VolumePlanesScene::VolumePlanesScene()
{
}

void VolumePlanesScene::init()
{
  vertex = MarchingCubes::instance()->march(data, 800);
  vertex = MarchingCubes::instance()->march(data, 800);
}

void VolumePlanesScene::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();

  glTranslated(0,0,zoom_*kZoomFactor);
  glRotatef(rotx_,1,0,0);
  glRotatef(roty_,0,1,0);

  glBegin(GL_TRIANGLES);
  for(int i=0;i<vertex.size();i++){
    glVertex3f(vertex[i].x(),vertex[i].y(),vertex[i].z());
  }
  glEnd();
}

void VolumePlanesScene::release()
{
  MarchingCubes::instance()->release();
}
