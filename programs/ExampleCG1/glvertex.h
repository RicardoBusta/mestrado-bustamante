#ifndef GLVERTEX_H
#define GLVERTEX_H

#include "vector4.h"
#include <QColor>

class GLVertex
{
public:
  GLVertex();
  GLVertex(const Vector4 &v, const QColor &c);

  Vector4 v_;
  QColor c_;
};

#endif // GLVERTEX_H
