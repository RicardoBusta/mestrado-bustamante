#include "structures.h"

#include <cmath>

#include <QDebug>

namespace Ric{

  Vector operator*(const double &d, const Vector &v)
  {
    return Vector(v.x()*d,v.y()*d,v.z()*d,v.w()*d);
  }


  Vector operator*(const Vector &v, const double &d)
  {
    return Vector(v.x()*d,v.y()*d,v.z()*d,v.w()*d);
  }


  Vector operator*(const Matrix4x4 & d, const Vector &v)
  {
    return Vector (
          d.data(0)*v.x() + d.data(4)*v.y() + d.data(8)*v.z() + d.data(12)*v.w() ,
        d.data(1)*v.x() + d.data(5)*v.y() + d.data(9)*v.z() + d.data(13)*v.w() ,
        d.data(2)*v.x() + d.data(6)*v.y() + d.data(10)*v.z() + d.data(14)*v.w() ,
        d.data(3)*v.x() + d.data(7)*v.y() + d.data(11)*v.z() + d.data(15)*v.w()
        );
  }


  Vector operator*(const Vector & v, const Matrix4x4 & d)
  {
    return Vector (
          d.data(0)*v.x() + d.data(1)*v.y() + d.data(2)*v.z() + d.data(3)*v.w() ,
        d.data(4)*v.x() + d.data(5)*v.y() + d.data(6)*v.z() + d.data(7)*v.w() ,
        d.data(8)*v.x() + d.data(9)*v.y() + d.data(10)*v.z() + d.data(11)*v.w() ,
        d.data(12)*v.x() + d.data(13)*v.y() + d.data(14)*v.z() + d.data(15)*v.w()
        );
  }


  Vector operator^(const Vector &v1, const Vector &v2)
  {
    return Vector(
          v1.y()*v2.z() - v1.z()*v2.y(),
          v1.z()*v2.x() - v1.x()*v2.z(),
          v1.x()*v2.y() - v1.y()*v2.x(),
          0
          );
  }


  Vector operator+(const Vector &v1, const Vector &v2)
  {
    return Vector(
          v1.x() + v2.x(),
          v1.y() + v2.y(),
          v1.z() + v2.z(),
          v1.w() + v2.w()
          );
  }

  Vector operator+=(Vector &v1, const Vector &v2)
  {
    v1.setX( v1.x() + v2.x() );
    v1.setY( v1.y() + v2.y() );
    v1.setZ( v1.z() + v2.z() );
    v1.setW( v1.w() + v2.w() );
    return v1;
  }


  double operator*(const Vector &v1, const Vector &v2)
  {
    return (
          (v1.x() * v2.x()) +
          (v1.y() * v2.y()) +
          (v1.z() * v2.z())
          );
  }


  Vector operator-(const Vector &v)
  {
    return Vector(
          -v.x(),
          -v.y(),
          -v.z(),
          -v.w()
          );
  }


  Vector operator-(const Vector &v1, const Vector &v2)
  {
    return Vector(
          v1.x()-v2.x(),
          v1.y()-v2.y(),
          v1.z()-v2.z(),
          v1.w()-v2.w()
          );
  }


  Vector operator/(const Vector &v, const double &d)
  {
    return Vector(
          v.x()/d,
          v.y()/d,
          v.z()/d,
          v.w()/d
          );
  }


  Matrix4x4 operator*(const Matrix4x4 & m1, const Matrix4x4 & m2)
  {
    Matrix4x4 mr;
    for(int i=0;i<4;i++){
      for(int j=0;j<4;j++){
        mr.setData(i+(j*4),0);
        for(int k=0;k<4;k++){
          mr.setData(i+(j*4),mr.data(i+(j*4)) + m1.data(i+(k*4))*m2.data(k+(j*4)));
        }
      }
    }
    return mr;
  }

  QDebug operator<<(QDebug d, const Vector &v)
  {
    d.nospace()<<"Vector("<< v.x() << "," << v.y() << "," << v.z() << "," << v.w() << ") Length("<<v.Length()<<")";
    return d.space();
  }

  QDebug operator<<(QDebug d, const Matrix4x4 &m)
  {
    d.nospace()<<"Matrix4x4(";
    for(int i=0;i<4;i++){
      for(int j=0;j<4;j++){
        d << m.data(i+(j*4))<< " ";
      }
      d<< "\n";
    }
    d<<")";
    return d.space();
  }

  QDebug operator<<(QDebug d, const Color &c)
  {
    d<<"Color("<<c.r()<<","<<c.b()<<","<<c.b()<<") - rgba("<< hex << c.Argb()<<")";
    return d;
  }

  Color operator*(const Color &v, const double &d)
  {
    return Color(
          v.r()*d,
          v.g()*d,
          v.b()*d
          );
  }

  Color operator*(const double &d, const Color &v)
  {
    return Color(
          v.r()*d,
          v.g()*d,
          v.b()*d
          );
  }

  Color operator^(const Color &v, const double &d)
  {
    return Color(
          pow(v.r(),d),
          pow(v.g(),d),
          pow(v.b(),d)
          );
  }

  Color operator+(const Color &c1, const Color &c2)
  {
    return Color(
          c1.r()+c2.r(),
          c1.g()+c2.g(),
          c1.b()+c2.b()
          );
  }

  void operator+=(Color &c1, const Color &c2)
  {
    c1 = c1+c2;
  }

  Color operator*(const Color &c1, const Color &c2)
  {
    return Color(
          c1.r()*c2.r(),
          c1.g()*c2.g(),
          c1.b()*c2.b()
          );
  }

  QDebug operator<<(QDebug d, const Material &m)
  {
    d.nospace()<<"Diffuse: "<<m.diffuse()<<"\n";
    d<<"Specular: "<<m.specular()<<"\n";
    d<<"Ambient: "<<m.ambient()<<"\n";
    d<<"Shininess: "<<m.shininess();
    return d.space();
  }

  Color operator/(const Color &c, const double &d)
  {
    return Color(
          c.r()/d,
          c.g()/d,
          c.b()/d
          );
  }

}
