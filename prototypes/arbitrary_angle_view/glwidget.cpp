#include "glwidget.h"

#include <QtOpenGL>
#include <QTimer>
#include <cmath>
#include <QDebug>

//#define TOP_VIEW

const int kslices = 36;
const float kangle = 360.0f;

void drawFloor(){
  glBegin(GL_QUADS);
  glVertex3f(-1,0,-1);
  glVertex3f(+1,0,-1);
  glVertex3f(+1,0,+1);
  glVertex3f(-1,0,+1);
  glEnd();
}

void drawBox(){
  glBegin(GL_QUADS);        // Draw The Cube Using quads
    glColor3f(0.0f,1.0f,0.0f);    // Color Blue
    glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Bottom Left Of The Quad (Top)
    glVertex3f( 1.0f, 1.0f, 1.0f);    // Bottom Right Of The Quad (Top)
    glColor3f(1.0f,0.5f,0.0f);    // Color Orange
    glVertex3f( 1.0f,-1.0f, 1.0f);    // Top Right Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f, 1.0f);    // Top Left Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Bottom)
    glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Bottom)
    glColor3f(1.0f,0.0f,0.0f);    // Color Red
    glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Front)
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Front)
    glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Front)
    glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Front)
    glColor3f(1.0f,1.0f,0.0f);    // Color Yellow
    glVertex3f( 1.0f,-1.0f,-1.0f);    // Top Right Of The Quad (Back)
    glVertex3f(-1.0f,-1.0f,-1.0f);    // Top Left Of The Quad (Back)
    glVertex3f(-1.0f, 1.0f,-1.0f);    // Bottom Left Of The Quad (Back)
    glVertex3f( 1.0f, 1.0f,-1.0f);    // Bottom Right Of The Quad (Back)
    glColor3f(0.0f,0.0f,1.0f);    // Color Blue
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Left)
    glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Left)
    glColor3f(1.0f,0.0f,1.0f);    // Color Violet
    glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Right)
    glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Right)
    glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Right)
    glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Right)
  glEnd();            // End Drawing The Cube - See more at: http://www.codemiles.com/c-opengl-examples/draw-3d-cube-using-opengl-t9018.html#sthash.x6Y4QUsf.dpuf
}

void drawScene(float angle){
  glPushMatrix();
  glRotatef(angle,0,1,0);
  glPushMatrix();
  glTranslated(0,0,3);
  drawBox();
  glPopMatrix();
  glPushMatrix();
  glTranslated(2,0,3);
  drawBox();
  glPopMatrix();
  glPushMatrix();
  glTranslated(-2,0,3);
  drawBox();
  glPopMatrix();
  glPushMatrix();
  glTranslated(-3,0,-3);
  drawBox();
  glPopMatrix();
  glPushMatrix();
  glTranslated(3,0,-3);
  drawBox();
  glPopMatrix();
  glPopMatrix();
}

void setFrustum(float nearv, float farv, float fovx, float fovy){
  float width = nearv * tan(fovx * M_PI/180.0f);
  float height = nearv * tan(fovy * M_PI/180.0f);
  glFrustum(-width,width,-height,height,nearv,farv);
}

GLWidget::GLWidget(QWidget *parent):
  QGLWidget(parent),
  rot_angle(0)
{
  QTimer *timer = new QTimer(this);
  QObject::connect(timer,SIGNAL(timeout()),this,SLOT(updateAngle()));
  timer->start(1000/60);
}

GLWidget::~GLWidget()
{
  clearGL();
}

void GLWidget::initializeGL()
{
  glEnable(GL_DEPTH_TEST);
}

void GLWidget::resizeGL(int w, int h)
{

}

void GLWidget::paintGL()
{
  glClearColor(0,0,0,0);
  glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

#ifdef TOP_VIEW
  float angle = 45;
  int slices = 1;
#else
  float angle = kangle;
  int slices = kslices;
#endif

  float angle_fov = (angle)/float(slices*2);
  float half_angle = angle/2.0f;

  for(int i=0;i<slices;i++){
    glViewport((i*width())/(slices),0,width()/(slices),height());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef TOP_VIEW
    setFrustum(0.1,1000,45,45);
    glTranslatef(0,0,-10);
#else
    setFrustum(0.1,1000,angle_fov,45);
    glRotatef( (-half_angle) + (2*i+1)*angle_fov,0,1,0);
#endif
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
#ifdef TOP_VIEW
    glRotatef(90,1,0,0);
#endif
    drawScene(rot_angle);
  }
}

void GLWidget::clearGL()
{

}

void GLWidget::updateAngle()
{
  rot_angle+=0.5;
  updateGL();
}

