#include "glvertex.h"

GLVertex::GLVertex()
{

}

GLVertex::GLVertex(const Vector4 &v, const QColor &c)
{
  v_ = v;
  c_ = c;
}
