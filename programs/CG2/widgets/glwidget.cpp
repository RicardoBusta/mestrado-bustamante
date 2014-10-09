#include "glwidget.h"

#include "scene/scene.h"
#include "scene/sceneobject.h"
#include "scene/openglauxfunctions.h"

#include <QDebug>
//#include <QMatrix4x4>
#include "ray.h"
#include <cmath>
#include <QMouseEvent>
#include <QWheelEvent>

#include "scene/triangleface.h"
#include "constants.h"

const QImage texture("://models/cubes.png");

// FoV

GLWidget::GLWidget(Scene *scene, QWidget *parent) :
  QGLWidget(parent),
  scene_(scene)
{
}

void GLWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  glPushAttrib(GL_ALL_ATTRIB_BITS);//2
  //  glDisable(GL_LIGHTING);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  Frustum(scene_->fov,scene_->ratio,scene_->near_plane_z,scene_->far_plane_z);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  foreach(SceneObject o,scene_->transformed_object_){
    //    glEnable(GL_LIGHTING);
    o.GlDraw(true,scene_->draw_bounding_box_);
  }

  glPointSize(10);
  glDisable(GL_DEPTH_TEST);
  glBegin(GL_POINTS);//3
  foreach(SceneLight l,scene_->transformed_light){
    glColor3f(1,1,1);
    Gl::Vertex3f(l.position);
  }
  glEnd();//3
  glPointSize(6);
  glBegin(GL_POINTS);//4
  foreach(SceneLight l,scene_->transformed_light){
    Gl::Color3f(l.material.diffuse());
    Gl::Vertex3f(l.position);
  }
  glEnd();//4

  glPopAttrib();//2

  glFlush();
}

void GLWidget::initializeGL()
{
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  glClearColor(0,0,0,1);

  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_COLOR_MATERIAL);

  qDebug() << texture.isNull();

  glEnable(GL_TEXTURE_2D);
  bindTexture(texture,GL_TEXTURE_2D);

  //  GLfloat position[] = {0.0f,0.0f,0.0f};
  //  GLfloat ambient[] = {0.2f,0.2f,0.2f,1.0f};
  //  GLfloat diffuse[] = {1.0f,1.0f,1.0f,1.0f};
  //  GLfloat specular[] = {1.0f,1.0f,1.0f,1.0f};

  glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);

  //  glLightfv(GL_LIGHT0,GL_POSITION,position);
  //  glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
  //  glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
  //  glLightfv(GL_LIGHT0,GL_SPECULAR,specular);

  glFlush();
}

void GLWidget::resizeGL(int w, int h)
{
  int size = qMin(w,h);
  glViewport((w-size)/2,(h-size)/2,size,size);
}

int GLWidget::heightForWidth(int w) const
{
  return w;
}

void GLWidget::Frustum(const float &fov, const float &ratio, const float &n, const float &f)
{
  float frustum_angle_x_ = (fov)*(M_PI/180.0f);
  float frustum_angle_y_ = (fov*ratio)*(M_PI/180.0f);
  float near_ = n;
  float far_ = f;

  float kFrustumSideX = near_ * tan(frustum_angle_x_/2.0f);
  float kFrustumSideY = near_ * tan(frustum_angle_y_/2.0f);

  glFrustum(-kFrustumSideX,kFrustumSideX,-kFrustumSideY,kFrustumSideY,near_,far_);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
  emit MousePressed(event);
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
  emit MouseReleased(event);
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
  emit MouseMoved(event);
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
  emit Wheel(event);
}
