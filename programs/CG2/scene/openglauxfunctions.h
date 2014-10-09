#ifndef OPENGLAUXFUNCTIONS_H
#define OPENGLAUXFUNCTIONS_H

namespace Ric{
  class Vector;
  class Color;
}

namespace Gl{
  void Vertex3f( const Ric::Vector &v );
  void Normal3f( const Ric::Vector &v );
  void Color3f( const Ric::Color &c );
  void TexCoord( const Ric::Vector &v );
}

#endif // OPENGLAUXFUNCTIONS_H
