#include "volumeplanesscene.h"

#include <QtOpenGL>
#include <QDebug>

const float kZoomFactor = 0.001f;

const unsigned int layers = 10;

VolumePlanesScene::VolumePlanesScene()
{
}

void VolumePlanesScene::init()
{
  glGenTextures(1,&textureID);
  glBindTexture(GL_TEXTURE_3D,textureID);

  glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void VolumePlanesScene::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glTranslated(0,0,zoom_*kZoomFactor);
  glRotatef(rotx_,1,0,0);
  glRotatef(roty_,0,1,0);

  glBegin(GL_QUADS);
  for(int i=0;i<layers;i++){
    float z = 1.0f-(float(2*i)/float(layers-1));
    glVertex3f(-1,-1,z);
    glVertex3f( 1,-1,z);
    glVertex3f( 1, 1,z);
    glVertex3f(-1, 1,z);
  }
  glEnd();
}

void VolumePlanesScene::release()
{

}
