#include "volumeplanesscene.h"

#include <QtOpenGL>
#include <QDebug>

#include "busta_libs/opengl_extension_manager/openglextensionmanager.h"

#include "data/volumedata.h"

const float kZoomFactor = 0.001f;

VolumePlanesScene::VolumePlanesScene()
{
  layers = 256;
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

  setTex3D();
}

void VolumePlanesScene::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glTranslated(0,0,zoom_*kZoomFactor);

  glMatrixMode(GL_TEXTURE);
  glLoadIdentity();
  glTranslatef(0.5,0.5,0.5);
  glRotatef(-roty_,0,1,0);
  glRotatef(-rotx_,1,0,0);
  glScalef(2,2,2);
  glTranslatef(-0.5,-0.5,-0.5);
  glMatrixMode(GL_MODELVIEW);
  glColor4f(1,1,1,1);

  glEnable(GL_TEXTURE_3D);
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

  glDisable(GL_TEXTURE_3D);
  glRotatef(rotx_,1,0,0);
  glRotatef(roty_,0,1,0);
  glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(1,0,0);

    glColor3f(0,1,0);
    glVertex3f(0,0,0);
    glVertex3f(0,1,0);

    glColor3f(0,0,1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,1);
  glEnd();
}

void VolumePlanesScene::release()
{

}

void VolumePlanesScene::setTex3D()
{
  glDeleteTextures(1,&textureID);
  glGenTextures(1,&textureID);
  glBindTexture(GL_TEXTURE_3D,textureID);

  glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  GLsizei tex_width = 256;
  GLsizei tex_height = 256;
  GLsizei tex_depth = 256;
  GLubyte *tex_data = new GLubyte[tex_width*tex_height*tex_depth*4];

  VolumeData data;
  data.load(file_name);

  for(int i=0;i<tex_height;i++){
    float fi = float(i)/float(tex_height-1);
    for(int j=0;j<tex_width;j++){
      float fj = float(j)/float(tex_width-1);
      for(int k=0;k<tex_depth;k++){
        float fk = float(k)/float(tex_depth-1);
//        float val = data.getInterpolatedValue(fi,fj,fk);
        float val = data.getValue256(i,j,k);
        int coord = 4*(i + tex_height*(j + tex_width*k));
        // Cut the borders
        if(i==0 || j==0 || k==0 || i==tex_height-1 || j==tex_width-1 || k==tex_depth-1){
          tex_data[coord+0]=0;
          tex_data[coord+1]=0;
          tex_data[coord+2]=0;
          tex_data[coord+3]=0;
        }else{
          transferFunction(val,&tex_data[coord]);
        }
      }
    }
  }

  Busta::OpenGL::instance()->texImage3D(GL_TEXTURE_3D,0,GL_RGBA,tex_width,tex_height,tex_depth,0,GL_RGBA,GL_UNSIGNED_BYTE,tex_data);
}

void VolumePlanesScene::transferFunction(unsigned short val, unsigned char *ret)
{

 if(val > 210){
   ret[0] = 0xff;
   ret[1] = 0xff;
   ret[2] = 0xff;
   ret[3] = 0x09;
 }else if(val > 150){
   ret[0] = 0xff;
   ret[1] = 0x0;
   ret[2] = 0x0;
   ret[3] = 0x09;
 }else if(val > 100){
   ret[0] = 0xff;
   ret[1] = 0xff;
   ret[2] = 0x0;
   ret[3] = 0x09;
 }else{
   ret[0] = 0xff;
   ret[1] = 0xff;
   ret[2] = 0xff;
   ret[3] = 0x00;
 }
}
