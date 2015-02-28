#include "glwidget.h"

#include <QtOpenGL>
#include <QTimer>
#include <cmath>
#include <QDebug>

#include "busta_libs/opengl_extension_manager/openglextensionmanager.h"

const unsigned int w = 256;
const unsigned int h = 48;

void drawFloor(){
  glBegin(GL_QUADS);
  glColor3f(0,0.5,0);
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
  glTranslated(-3,0,0);
  drawBox();
  glPopMatrix();
  glPushMatrix();
  glTranslated(3,0,0);
  drawBox();
  glPopMatrix();
  glPushMatrix();
  glTranslated(0,0,-3);
  drawBox();
  glPopMatrix();
  glPushMatrix();
  glTranslated(0,0,3);
  drawBox();
  glPopMatrix();
  glPushMatrix();
  glTranslated(3,0,3);
  drawBox();
  glPopMatrix();
  glPushMatrix();
  glTranslated(-3,0,3);
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
  glPushMatrix();
  glScalef(5,1,5);
  glTranslatef(0,-1,0);
  drawFloor();
  glPopMatrix();
  glPopMatrix();
}

void setFrustum(float nearv, float farv, float fovx, float fovy){
  float width = nearv * tan(fovx * M_PI/180.0f);
  float height = nearv * tan(fovy * M_PI/180.0f);
  glFrustum(-width,width,-height,height,nearv,farv);
}

AAVGLWidget::AAVGLWidget(QWidget *parent):
  QGLWidget(parent),
  rot_angle_x(0),
  fov_angle(90),
  slices_num(1)
{
//  QTimer *timer = new QTimer(this);
//  QObject::connect(timer,SIGNAL(timeout()),this,SLOT(updateAngle()));
//  timer->start(1000/60);
}

AAVGLWidget::~AAVGLWidget()
{
  clearGL();
}

void AAVGLWidget::initializeGL()
{
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_COLOR_MATERIAL);

  Busta::OpenGL::instance()->glGenFramebuffers(1, &framebuffer);
  Busta::OpenGL::instance()->glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

  glGenTextures(1, &render_texture);
  glBindTexture(GL_TEXTURE_2D, render_texture);
  glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, w, h, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  Busta::OpenGL::instance()->glGenRenderbuffers(1, &depth_buffer);
  Busta::OpenGL::instance()->glBindRenderbuffer(GL_RENDERBUFFER, depth_buffer);
  Busta::OpenGL::instance()->glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, w, h);
  Busta::OpenGL::instance()->glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_buffer);

  Busta::OpenGL::instance()->glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, render_texture, 0);
  GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
  Busta::OpenGL::instance()->glDrawBuffers(1, DrawBuffers);

  //glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT24, w, h, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);

  if(Busta::OpenGL::instance()->glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
  return;
}

void AAVGLWidget::resizeGL(int w, int h)
{

}

void AAVGLWidget::paintGL()
{
  Busta::OpenGL::instance()->glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
  glViewport(0,0,w,h);

  glClearColor(0,0,0,1);
  glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

  float val_angle = (fov_angle)/float(slices_num*2);
  float half_angle = fov_angle/2.0f;

  glDisable(GL_TEXTURE_2D);

  for(int i=0;i<slices_num;i++){
    glViewport((i*w)/(slices_num),0,(w)/(slices_num),h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    setFrustum(0.1,1000,val_angle ,45);
    glRotatef( (-half_angle) + (2*i+1)*val_angle ,0,1,0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    drawScene(rot_angle_x);
  }

  glFlush();
  glFinish();

  Busta::OpenGL::instance()->glBindFramebuffer(GL_FRAMEBUFFER, 0);

  glViewport(0,0,width(),height());
  glClearColor(0,0,1,1);
  glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glEnable(GL_TEXTURE_2D);
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0,0);
  glVertex3f(-0.9,-0.9,0);
  glTexCoord2f(1,0);
  glVertex3f( 0.9,-0.9,0);
  glTexCoord2f(1,1);
  glVertex3f( 0.9, 0.9,0);
  glTexCoord2f(0,1);
  glVertex3f(-0.9, 0.9,0);
  glEnd();

  glFinish();
}

void AAVGLWidget::clearGL()
{

}

void AAVGLWidget::updateXRotation(int xr)
{
  rot_angle_x=float(xr)/10.0f;
  updateGL();
}

void AAVGLWidget::updateYRotation(int yr)
{
  rot_angle_y=float(yr)/10.0f;
  updateGL();
}

void AAVGLWidget::updateFoVAngle(int angle)
{
  fov_angle = float(angle)/10.0f;
  updateGL();
}

void AAVGLWidget::updateSlices(int slices)
{
  slices_num = slices;
  updateGL();
}

