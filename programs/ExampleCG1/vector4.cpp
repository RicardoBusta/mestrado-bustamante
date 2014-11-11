/*
 * 4D Vector Class by Ricardo Bustamante de Queiroz
 * e-mail: ricardobqueiroz@gmail.com
 */

#include "vector4.h"

#include "matrix4x4.h"

#include <QtMath>

Vector4::Vector4()
{
  std::fill(data_,data_+4,0);
}

Vector4::Vector4(const Vector4 &v)
{
  memcpy(data_,v.data_,4*sizeof(float));
}

Vector4::Vector4(float x, float y, float z, float w)
{
  data_[0] = x;
  data_[1] = y;
  data_[2] = z;
  data_[3] = w;
}

void Vector4::setData(const int &i, const float &value)
{
  data_[i] = value;
}

void Vector4::addData(const int &i, const float &value)
{
  data_[i] += value;
}

float Vector4::data(const int i) const
{
  return data_[i];
}

const float *Vector4::data() const
{
  return data_;
}

void Vector4::setPoint(float x, float y, float z)
{
  data_[0] = x;
  data_[1] = y;
  data_[2] = z;
  data_[3] = 1;
}

void Vector4::setVector(float x, float y, float z)
{
  data_[0] = x;
  data_[1] = y;
  data_[2] = z;
  data_[3] = 0;
}

float Vector4::x() const
{
  return data_[0];
}

float Vector4::y() const
{
  return data_[1];
}

float Vector4::z() const
{
  return data_[2];
}

float Vector4::w() const
{
  return data_[3];
}

Vector4 Vector4::operator=(const Vector4 &v)
{
  memcpy(data_,v.data_,4*sizeof(float));
  return *this;
}

float Vector4::length() const
{
  return qSqrt( (data_[0]*data_[0]) + (data_[1]*data_[1]) + (data_[2]*data_[2]) + (data_[3]*data_[3]) );
}

Vector4 Vector4::normalized() const
{
  Vector4 result = *this;
  float len = length();
  for(int i=0;i<4;i++){
    result.setData(i,result.data(i)/len);
  }
  return result;
}

Vector4 Vector4::reflect(const Vector4 &incident, const Vector4 &normal)
{
  return (incident - 2.0f * dot(normal,incident) * normal);
}

float Vector4::dot(const Vector4 &v1, const Vector4 &v2)
{
  float res = 0;
  for(int i=0;i<4;i++){
    res += v1.data(i)*v1.data(i);
  }
  return res;
}

Vector4 Vector4::clamp(const Vector4 &v, float min, float max)
{
  Vector4 result;
  for(int i=0;i<4;i++){
    result.setData(i,qMax(qMin(max,v.data(i)),min));
  }
  return result;
}

std::ostream &operator<<(std::ostream &os, const Vector4 &dt)
{
  os << "("<<dt.data(0)<<", "<<dt.data(1)<<", "<<dt.data(2)<<", "<<dt.data(3)<<")";
  return os;
}


Vector4 operator*(const Vector4 &v1, const Matrix4x4 &m2)
{
  Vector4 result;
  for(int j=0;j<4;j++){
    result.setData(j, 0.0f);
    for(int k=0;k<4;k++){
      result.addData(j, v1.data(k)*m2.data(k,j));
    }
  }

  if(v1.w()!=0 && v1.w()!=1){
    result.setPoint(result.x()/result.w(),
                    result.y()/result.w(),
                    result.z()/result.w());
  }

  return result;
}


Vector4 operator-(const Vector4 &v1, const Vector4 &v2)
{
  Vector4 result;
  for(int i=0;i<4;i++){
    result.setData(i,v1.data(i)-v2.data(i));
  }
  return result;
}


Vector4 operator+(const Vector4 &v1, const Vector4 &v2)
{
  Vector4 result;
  for(int i=0;i<4;i++){
    result.setData(i,v1.data(i)+v2.data(i));
  }
  return result;
}


Vector4 operator-(const Vector4 &v1)
{
  Vector4 result;
  for(int i=0;i<4;i++){
    result.setData(i,-v1.data(i));
  }
  return result;
}


Vector4 operator*(const float &f1, const Vector4 &v2)
{
  Vector4 result;
  for(int i=0;i<4;i++){
    result.setData(i,f1*v2.data(i));
  }
  return result;
}


Vector4 operator*(const Vector4 &v1, const float &f2)
{
  return f2*v1;
}
