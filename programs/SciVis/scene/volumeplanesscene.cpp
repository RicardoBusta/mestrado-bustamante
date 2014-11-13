#include "volumeplanesscene.h"

#include <QtOpenGL>
#include <QDebug>

#include "busta_libs/opengl_extension_manager/openglextensionmanager.h"

#include "data/volumedata.h"

const float kZoomFactor = 0.001f;

const unsigned int layers = 10;

VolumePlanesScene::VolumePlanesScene()
{
}

void VolumePlanesScene::init()
{
  glEnable(GL_TEXTURE_3D);
  glEnable(GL_CULL_FACE);
//  glEnable(GL_DEPTH_TEST);
//  glEnable ( GL_ALPHA_TEST ) ;
  //glAlphaFunc ( GL_GREATER, 0.1f ) ;
//  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable( GL_BLEND );

  glGenTextures(1,&textureID);
  glBindTexture(GL_TEXTURE_3D,textureID);

  glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  GLsizei tex_side = 20;
  GLubyte *tex_data = new GLubyte[tex_side*tex_side*tex_side];

  VolumeData data;

  for(int i=0;i<tex_side;i++){
    float fi = float(i)/float(tex_side-1);
    for(int j=0;j<tex_side;j++){
      float fj = float(j)/float(tex_side-1);
      for(int k=0;k<tex_side;k++){
        float fk = float(k)/float(tex_side-1);
        //qDebug() << data.getNormalizedValues(fi,fj,fk);
        tex_data[i + tex_side*(j + tex_side*k)] = data.getNormalizedValues(fi,fj,fk)*0xff;
      }
    }
  }

  qDebug() << "Normalized vallues:" << data.getNormalizedValues(1,0,0);

  Busta::OpenGL::instance()->texImage3D(GL_TEXTURE_3D,0,GL_ALPHA,tex_side,tex_side,tex_side,0,GL_ALPHA,GL_UNSIGNED_BYTE,tex_data);
}

void VolumePlanesScene::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glTranslated(0,0,zoom_*kZoomFactor);
  glRotatef(rotx_,1,0,0);
  glRotatef(roty_,0,1,0);

  glColor4f(1,1,1,1);

  glBegin(GL_QUADS);
  for(int i=0;i<layers;i++){
    float tz = float(i)/float(layers-1);
    float z = -1.0f+(2.0f*tz);
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
