#include "openglauxfunctions.h"

#include "structures.h"
#ifdef _WIN32
#include <Windows.h>
#endif
#include <GL/gl.h>
//#include <QtOpenGL>

namespace Gl{

void Vertex3f(const Ric::Vector &v)
{
  glVertex3f(v.x(),v.y(),v.z());
}

void Normal3f(const Ric::Vector &v)
{
  glNormal3f(v.x(),v.y(),v.z());
}

void Color3f(const Ric::Color &c)
{
  glColor3d(c.r(), c.g(), c.b());
}

void TexCoord(const Ric::Vector &v)
{
  glTexCoord2f(v.x(),v.y());
}

}
