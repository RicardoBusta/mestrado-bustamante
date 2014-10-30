#include "volumeplanesscene.h"

#include <QtOpenGL>
#include <QDebug>

#include "busta_libs/opengl_extension_manager/openglextensionmanager.h"

const float kZoomFactor = 0.001f;

const unsigned int layers = 10;

VolumePlanesScene::VolumePlanesScene()
{
}

void VolumePlanesScene::init()
{
  glEnable(GL_TEXTURE_3D);

  glGenTextures(1,&textureID);
  glBindTexture(GL_TEXTURE_3D,textureID);

  glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  GLsizei tex_side = 20;
  GLubyte *tex_data = new GLubyte[tex_side*tex_side*tex_side];

  for(int i=0;i<tex_side;i++){
    for(int j=0;j<tex_side;j++){
      for(int k=0;k<tex_side;k++){
        tex_data[i + tex_side*(j + tex_side*k)] = 0x66;
      }
    }
  }

  Busta::OpenGL::instance()->texImage3D(GL_TEXTURE_3D,0,GL_LUMINANCE_ALPHA,tex_side,tex_side,tex_side,0,GL_LUMINANCE,GL_UNSIGNED_BYTE,tex_data);
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
    float tz = float(i)/float(layers-1);
    float z = 1.0f-(2.0f*tz);
    glTexCoord3f(0,0,tz);
    glVertex3f(-1,-1,z);
    glTexCoord3f(1,0,tz);
    glVertex3f( 1,-1,z);
    glTexCoord3f(1,1,tz);
    glVertex3f( 1, 1,z);
    glTexCoord3f(0,1,tz);
    glVertex3f(-1, 1,z);
  }
  glEnd();
}

void VolumePlanesScene::release()
{

}
