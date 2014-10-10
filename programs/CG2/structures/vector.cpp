#include "vector.h"

#include <cmath>

namespace Ric{

  Vector::Vector()
    : x_(0),
      y_(0),
      z_(0),
      w_(1)
  {}

  Vector::Vector(const double x, const double y, const double z)
    : x_(x),
      y_(y),
      z_(z),
      w_(1)
  {}

  Vector::Vector(const double x, const double y, const double z, const double w)
    : x_(x),
      y_(y),
      z_(z),
      w_(w)
  {}

  Vector::Vector(const Vector *v, const Matrix4x4 *m)
  {
    (*this) = (*v);
    this->w_ = 1;
    (*this) = (*m)*(*this);
    (*this) = this->Affine();
  }

  Vector::Vector(QVector3D v)
  {
    this->x_ = v.x();
    this->y_ = v.y();
    this->z_ = v.z();
  }

  Vector::Vector(QVector2D v)
  {
    this->x_ = v.x();
    this->y_ = v.y();
  }

  Vector Vector::Normalized() const
  {
    if(Length()>0){
      return ((*this)/Length());
    }else{
      return *this;
    }
  }

  Vector Vector::Affine() const
  {
    if(w_!=0){
      return Vector(x_/w_,y_/w_,z_/w_,1);
    }
    else
      return Vector(0,0,0);
  }

  double Vector::Length() const
  {
    return sqrt(x_*x_ + y_*y_ + z_*z_);
  }

  double Vector::x() const
  {
    return x_;
  }

  void Vector::setX(double x)
  {
    x_ = x;
  }

  double Vector::y() const
  {
    return y_;
  }

  void Vector::setY(double y)
  {
    y_ = y;
  }

  double Vector::z() const
  {
    return z_;
  }

  void Vector::setZ(double z)
  {
    z_ = z;
  }

  double Vector::w() const
  {
    return w_;
  }

  void Vector::setW(double w)
  {
    w_ = w;
  }

  Vector Vector::transformv(const Vector &v, const Matrix4x4 &m)
  {
    Vector r = v;
    r.setW(1);
    r = m*r;
    r = r.Affine();
    return r;
  }

  Vector Vector::operator=(const QVector2D &v)
  {
    this->x_ = v.x();
    this->y_ = v.y();
    return *this;
  }

  Vector Vector::operator=(const QVector3D &v)
  {
    this->x_ = v.x();
    this->y_ = v.y();
    this->z_ = v.z();
    return *this;
  }

  bool Vector::operator==(const Vector &v)
  {
    if(x_ != v.x() || y_ != v.y() || z_ != v.z()){
      return false;
    }
    return true;
  }

} // namespace
