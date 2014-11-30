#include "marchingcubesscene.h"

#include <QtOpenGL>
#include <QDebug>

#include "algorithm/marchingcubes.h"

const float kZoomFactor = 0.001f;

MarchingCubesScene::MarchingCubesScene()
{
}

void MarchingCubesScene::init()
{
  VolumeData data;

  data.load(file_name);

  QVector<QVector3D> vertex;

  qDebug() << "Marching" << cube_size << iso_value;
  vertex = MarchingCubes::instance()->march(data,cube_size,iso_value);

  glDeleteLists(display_list,1);
  display_list = glGenLists(1);

  glNewList(display_list, GL_COMPILE);
  glBegin(GL_TRIANGLES);
  for(int i=0;i+2<vertex.size();i+=3){
    QVector3D normal = QVector3D::crossProduct(vertex[i+1]-vertex[i],vertex[i+2]-vertex[i]);
    normal.normalize();
    glNormal3f(normal.x(),normal.y(),normal.z());
    glVertex3f(vertex[i].x(),vertex[i].y(),vertex[i].z());
    glVertex3f(vertex[i+1].x(),vertex[i+1].y(),vertex[i+1].z());
    glVertex3f(vertex[i+2].x(),vertex[i+2].y(),vertex[i+2].z());
  }
  glEnd();
  glEndList();
}

void MarchingCubesScene::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_COLOR_MATERIAL);
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

  glLoadIdentity();

  glTranslated(0,0,zoom_*kZoomFactor);
  glRotatef(rotx_,1,0,0);
  glRotatef(roty_,0,1,0);

  qDebug() << "color" << color;
  glColor3f(color.redF(),color.greenF(),color.blueF());
  glCallList(display_list);
}

void MarchingCubesScene::release()
{
  MarchingCubes::instance()->release();
}
