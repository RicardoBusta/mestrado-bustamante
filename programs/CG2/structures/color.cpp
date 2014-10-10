#include "color.h"

#include <QDebug>
#include <cmath>

namespace Ric{

Color::Color()
  : r_(0),
    g_(0),
    b_(0),
    null_(true)
{
}

Color::Color(unsigned int c)
    : r_(std::min((float((c&0x00ff0000)>>16))/255.0,1.0)),
      g_(std::min((float((c&0x0000ff00)>>8))/255.0,1.0)),
      b_(std::min((float(c&0x000000ff))/255.0,1.0)),
      null_(false)
  {
    if( 0x00000000 == (c&0x00ffffff) ){
      null_ = true;
    }
  }

  Color::Color(double r, double g, double b)
    : r_(std::min(r,1.0)),
      g_(std::min(g,1.0)),
      b_(std::min(b,1.0)),
      null_(false)
  {
    if( 0==r_ && 0==g_ && 0==b_ ){
      null_ = true;
    }
  }

  unsigned int Color::Argb() const
  {
    unsigned int rc = (unsigned int)(255)<<24 |
                                           (unsigned int)(r_*255)<<16 |
                                           (unsigned int)(g_*255)<<8 |
                                           (unsigned int)(b_*255) ;
    return rc;
  }

  Color Color::Cap()
  {
    if(r_<0) r_=0;
    if(r_>1) r_=1;
    if(g_<0) g_=0;
    if(g_>1) g_=1;
    if(b_<0) b_=0;
    if(b_>1) b_=1;
    return *this;
  }

  Color Color::operator=(const Color &c)
  {
    this->r_ = c.r_;
    this->g_ = c.g_;
    this->b_ = c.b_;
    return *this;
  }

  bool Color::null()
  {
    return null_;
  }

  double Color::r() const
  {
      return r_;
  }

  double Color::g() const
  {
      return g_;
  }

  double Color::b() const
  {
      return b_;
  }
  
} // namespace
