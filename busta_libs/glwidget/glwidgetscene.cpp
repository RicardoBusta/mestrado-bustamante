#include "glwidgetscene.h"

#include <QtOpenGL>

namespace Busta{

GLWidgetScene::GLWidgetScene()
{
}

void GLWidgetScene::init()
{
//  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);
}

void GLWidgetScene::paint()
{
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  glBegin(GL_QUADS);
  glVertex3f(-1,-1,0);
  glVertex3f(+1,-1,0);
  glVertex3f(+1,+1,0);
  glVertex3f(-1,+1,0);
  glEnd();
}

void GLWidgetScene::projection()
{
  glMatrixMode(GL_PROJECTION);
//  glLoadIdentity();
//  glFrustum(-0.1,0.1,-0.1,0.1,0.1,10000.0);
//  glTranslated(0,0,-5);
  glMatrixMode(GL_MODELVIEW);
}

}
