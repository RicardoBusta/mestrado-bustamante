#ifndef VECTOR_H
#define VECTOR_H

#include <QVector3D>
#include <QVector2D>

namespace Ric{

class Vector;
class Matrix4x4;
Vector operator/(const Vector &v, const double &d);
Vector operator*(const Matrix4x4 &d, const Vector &v);

class Vector{
public:
  Vector();
  Vector(const double x, const double y, const double z);
  Vector(const double x,const double y, const double z, const double w);
  Vector(const Vector *v, const Matrix4x4 *m);
  Vector(QVector3D v);
  Vector(QVector2D v);

  Vector Normalized() const;
  Vector Affine() const;
  double Length() const;

  double x() const;
  void setX(double x);
  double y() const;
  void setY(double y);
  double z() const;
  void setZ(double z);
  double w() const;
  void setW(double w);

  static Vector transformv(const Vector &v, const Matrix4x4 &m);

  Vector operator=(const QVector2D &v);
  Vector operator=(const QVector3D &v);

  bool operator==(const Ric::Vector &v);
private:
  double x_;
  double y_;
  double z_;
  double w_;
};

} // namespace

#endif // VECTOR_H
