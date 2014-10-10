#include "outerviewwidget.h"

#include "scene/scene.h"
#include "ray.h"
#include <cmath>
#include <QMouseEvent>
#include <QWheelEvent>
#include "constants.h"

#include "scene/triangleface.h"
#include "scene/openglauxfunctions.h"

OuterViewWidget::OuterViewWidget(Scene *scene,QWidget *parent)
  : QGLWidget(parent),
    scene_(scene),
    rotx(45),
    roty(-45),
    distz(-30)
{
}

void OuterViewWidget::paintGL()
{
  //  if(!scene.valid_) return;
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  frustum(90.0f,1.0f,0.1f,1000.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glTranslated(0,0,-10+distz);
  glRotatef(rotx,1,0,0);
  glRotatef(roty,0,1,0);

  foreach(SceneObject o,scene_->object){
    glEnable(GL_LIGHTING);
    o.GlDraw(true,scene_->draw_bounding_box_);
  }

  const float propx = (1.0f/float(scene_->selected_image_size-1));
  const float propy = (1.0f/float(scene_->selected_image_size-1));
  float x = 0.5;//(float(scene_->specialx)*propx);
  float y = 0.5;//(float(scene_->specialy)*propy);
  Ric::Vector observer(0,0,0);
  Ric::Vector vfx1 = ((1-x)*scene_->frustum[8]) + ((x)*scene_->frustum[7]);
  Ric::Vector vfx2 = ((1-x)*scene_->frustum[5]) + ((x)*scene_->frustum[6]);
  Ric::Vector vnx1 = ((1-x)*scene_->frustum[4]) + ((x)*scene_->frustum[3]);
  Ric::Vector vnx2 = ((1-x)*scene_->frustum[1]) + ((x)*scene_->frustum[2]);
  Ric::Vector far_plane = (y*vfx1)+((1-y)*vfx2);
  Ric::Vector near_plane = (y*vnx1)+((1-y)*vnx2);

  Ray ray(observer,far_plane.Normalized(),far_plane.Length(), near_plane.Length(),Ric::Color(0xff000000));
  const TriangleFace *f = ray.cast(scene_);
  ray.calc(f,scene_,0,true);

  Ric::Vector n_b;

  if(f!=NULL){
  n_b = f->n_b(ray.b());
  }

  Ray shadow;
  if(scene_->light.size()>0){
    shadow = Ray(ray.p(),ray.l(),(scene_->light[0].position-ray.p()).Length(),near_plane.Length(),Ric::Color(0xff000000));
    shadow.cast(scene_);
  }

  // Calculate the points to draw ray interactions based on ray collisions.
  Ric::Vector vo[] = {
    ray.o(), //viewer
    ray.p(), //ray collision point
    ray.p() + (ray.n()*3), //ray normal
    ray.p() + (ray.l()*3),
    ray.p() + (ray.r()*3),
    shadow.p(),
    ray.p() + ((n_b)*3)
  };
  const int vo_size = 7;
  for(int i=0;i<vo_size;i++){
    vo[i].setW( 1 );
    vo[i] = scene_->ipvm*vo[i];
    vo[i] = vo[i].Affine();
  }

  glPushAttrib(GL_ALL_ATTRIB_BITS);//2
  glDisable(GL_LIGHTING);
  glLineWidth(5);

  if(scene_->track_one_ray && ray.hit()){

    glBegin(GL_LINES);//3
    color3f(ray.color());

    vertex3f(vo[0]);
    vertex3f(vo[1]);

    glColor3f(1,1,1);
    vertex3f(vo[1]);
    vertex3f(vo[2]);
    //      qDebug() << vo[1] << vo[2];

    glColor3f(1,0,0);
    vertex3f(vo[1]);
    vertex3f(vo[3]);

    glColor3f(0,1,0);
    vertex3f(vo[1]);
    vertex3f(vo[4]);

    if(shadow.hit()){
    glColor3f(1,1,1);
    }else{
    glColor3f(0,0,0);
    }
    vertex3f(vo[1]);
    vertex3f(vo[5]);

    glColor3f(1,1,0);
    vertex3f(vo[1]);
    vertex3f(vo[6]);

    glEnd();//3

  } // track_one_ray

  glPointSize(10);
  glDisable(GL_DEPTH_TEST);
  glBegin(GL_POINTS);//5
  foreach(SceneLight l,scene_->light){
    glColor3f(1,1,1);
    vertex3f(l.position);
  }
  glEnd();//5
  glPointSize(6);
  glBegin(GL_POINTS);//4
  foreach(SceneLight l,scene_->light){
    color3f(l.material.diffuse());
    vertex3f(l.position);
  }
  glEnd();//4


  glPopAttrib();//2


  glPushAttrib(GL_ALL_ATTRIB_BITS);
  glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
  glDisable(GL_CULL_FACE);
  glDisable(GL_LIGHTING);
  glBegin(GL_TRIANGLES);
  glColor4f(1,1,1,1);
  vertex3f(scene_->transformed_frustum[0]);
  vertex3f(scene_->transformed_frustum[1]);
  vertex3f(scene_->transformed_frustum[2]);

  vertex3f(scene_->transformed_frustum[0]);
  vertex3f(scene_->transformed_frustum[2]);
  vertex3f(scene_->transformed_frustum[3]);

  vertex3f(scene_->transformed_frustum[0]);
  vertex3f(scene_->transformed_frustum[3]);
  vertex3f(scene_->transformed_frustum[4]);

  vertex3f(scene_->transformed_frustum[0]);
  vertex3f(scene_->transformed_frustum[4]);
  vertex3f(scene_->transformed_frustum[1]);
  glEnd();
  glBegin(GL_QUADS);
  drawFrustum();
  glEnd();
  glPopAttrib();
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDisable(GL_LIGHTING);
  glFrontFace(GL_CW);
  glBegin(GL_QUADS);
  glColor4f(1,1,1,0.5);
  drawFrustum();
  glEnd();
  glFrontFace(GL_CCW);
  glBegin(GL_QUADS);
  glColor4f(1,1,1,0.5);
  drawFrustum();
  glEnd();
  glDisable(GL_BLEND);


//  Ric::Vector p1(-1,1,0);
//  Ric::Vector v1(-1,1,1);
//  v1 = v1.Normalized()*10;

//  Ric::Vector p2(1,1,0);
//  Ric::Vector v2(1,1,1);
//  v2 = v2.Normalized()*10;

//  Ric::Vector p3(-1,-1,0);
//  Ric::Vector v3(-1,-1,1);
//  v3 = v3.Normalized()*10;

//  Ric::Vector p4(1,-1,0);
//  Ric::Vector v4(1,-1,1);
//  v4 = v4.Normalized()*10;

//  glColor3f(1,1,1);
//  glDisable(GL_LIGHTING);
//  glBegin(GL_LINES);
//  Gl::Vertex3f(p1);
//  Gl::Vertex3f(p1+v1);

//  Gl::Vertex3f(p2);
//  Gl::Vertex3f(p2+v2);

//  Gl::Vertex3f(p3);
//  Gl::Vertex3f(p3+v3);

//  Gl::Vertex3f(p4);
//  Gl::Vertex3f(p4+v4);

//  const int xv = 10;
//  const int yv = 10;

//  for(int i=0;i<=xv;i++){
//    float percx = (float(i)/float(xv));

//    Ric::Vector p12 = percx*p1 + (1.0-percx)*p2;
//    Ric::Vector v12 = (percx*v1 + (1.0-percx)*v2).Normalized()*10;

//    Ric::Vector p34 = percx*p3 + (1.0-percx)*p4;
//    Ric::Vector v34 = (percx*v3 + (1.0-percx)*v4).Normalized()*10;
//    for(int j=0;j<=yv;j++){
//      float percy = (float(j)/float(yv));

//      Ric::Vector p1234 = percy*p12 + (1.0-percy)*p34;
//      Ric::Vector v1234 = (percy*v12 + (1.0-percy)*v34).Normalized()*10;
//      Gl::Vertex3f(p1234);
//      Gl::Vertex3f(p1234+v1234);
//    }
//  }
//  glEnd();

  glPopAttrib();

  glFlush();
}

void OuterViewWidget::initializeGL()
{
  glClearColor(0,0,0,1);

  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_COLOR_MATERIAL);

  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  glFlush();
}

void OuterViewWidget::resizeGL(int w, int h)
{
  int size = qMin(w,h);
  glViewport((w-size)/2,(h-size)/2,size,size);
}

int OuterViewWidget::heightForWidth(int w) const
{
  return w;
}

void OuterViewWidget::vertex3f(Ric::Vector v)
{
  glVertex3f(v.x(),v.y(),v.z());
}

void OuterViewWidget::normal3f(Ric::Vector v)
{
  glNormal3f(v.x(),v.y(),v.z());
}

void OuterViewWidget::color3f(Ric::Color c)
{
  glColor3d(c.r(), c.g(), c.b());
}

void OuterViewWidget::frustum(float fov, float ratio, float n, float f)
{
  float frustum_angle_x_ = (fov)*(M_PI/180.0f);
  float frustum_angle_y_ = (fov*ratio)*(M_PI/180.0f);
  float near_ = n;
  float far_ = f;

  float kFrustumSideX = near_ * tan(frustum_angle_x_/2.0f);
  float kFrustumSideY = near_ * tan(frustum_angle_y_/2.0f);

  glFrustum(-kFrustumSideX,kFrustumSideX,-kFrustumSideY,kFrustumSideY,near_,far_);
}

void OuterViewWidget::drawFrustum()
{
  //near face
  vertex3f(scene_->transformed_frustum[1]);
  vertex3f(scene_->transformed_frustum[2]);
  vertex3f(scene_->transformed_frustum[3]);
  vertex3f(scene_->transformed_frustum[4]);

  //top face
  vertex3f(scene_->transformed_frustum[4]);
  vertex3f(scene_->transformed_frustum[3]);
  vertex3f(scene_->transformed_frustum[7]);
  vertex3f(scene_->transformed_frustum[8]);

  //bot face
  vertex3f(scene_->transformed_frustum[1]);
  vertex3f(scene_->transformed_frustum[5]);
  vertex3f(scene_->transformed_frustum[6]);
  vertex3f(scene_->transformed_frustum[2]);

  //right face
  vertex3f(scene_->transformed_frustum[2]);
  vertex3f(scene_->transformed_frustum[6]);
  vertex3f(scene_->transformed_frustum[7]);
  vertex3f(scene_->transformed_frustum[3]);

  //left face
  vertex3f(scene_->transformed_frustum[1]);
  vertex3f(scene_->transformed_frustum[4]);
  vertex3f(scene_->transformed_frustum[8]);
  vertex3f(scene_->transformed_frustum[5]);

  //far face
  vertex3f(scene_->transformed_frustum[5]);
  vertex3f(scene_->transformed_frustum[8]);
  vertex3f(scene_->transformed_frustum[7]);
  vertex3f(scene_->transformed_frustum[6]);
}

void OuterViewWidget::mousePressEvent(QMouseEvent *event)
{
  last_pos = event->pos();
}

void OuterViewWidget::mouseReleaseEvent(QMouseEvent *event)
{
  Q_UNUSED(event);
}

void OuterViewWidget::mouseMoveEvent(QMouseEvent *event)
{
  QPoint delta = event->pos()-last_pos;
  last_pos = event->pos();
  rotx += float(delta.y())/2.0;
  roty += float(delta.x())/2.0;
  repaint();
}

void OuterViewWidget::wheelEvent(QWheelEvent *event)
{
  distz += float(event->delta())/100.0;
  repaint();
}
