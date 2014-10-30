/*
 * 4x4 Matrix Class by Ricardo Bustamante de Queiroz
 * e-mail: ricardobqueiroz@gmail.com
 */

#include "matrix4x4.h"

#include "vector4.h"

#include <cmath>

#ifndef M_PI
#  define M_PI 3.14159265358979323846
#endif

namespace Busta{

Matrix4x4::Matrix4x4():
  error_(false)
{
  loadIdentity();
}

Matrix4x4::Matrix4x4(const Matrix4x4 &m)
{
  memcpy(this->data_,m.data_,16*sizeof(float));
  this->error_ = m.error_;
}

Matrix4x4::Matrix4x4(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44)
{
  data_[0] = m11; data_[4] = m12; data_[8] = m13; data_[12] = m14;
  data_[1] = m21; data_[5] = m22; data_[9] = m23; data_[13] = m24;
  data_[2] = m31; data_[6] = m32; data_[10] = m33; data_[14] = m34;
  data_[3] = m41; data_[7] = m42; data_[11] = m43; data_[15] = m44;
}

Matrix4x4 Matrix4x4::operator=(const Matrix4x4 &m)
{
  memcpy(this->data_,m.data_,16*sizeof(float));
  this->error_ = m.error_;
  return *this;
}

bool Matrix4x4::error() const
{
  return error_;
}

void Matrix4x4::setData(float *data)
{
  memcpy(this->data_,data,16*sizeof(float));
}

void Matrix4x4::setData(const int &i, const int &j, const float &value)
{
  data_[i+(4*j)] = value;
}

void Matrix4x4::addData(const int &i, const int &j, const float &value)
{
  data_[i+(4*j)] += value;
}

float Matrix4x4::data(const int &i, const int &j) const
{
  return data_[i+(4*j)];
}

const float *Matrix4x4::data() const
{
  return data_;
}

void Matrix4x4::loadIdentity()
{
  std::fill(data_,data_+16,0.0f);
  data_[0] = data_[5] = data_[10] = data_[15] = 1.0f;
}

void Matrix4x4::rotate(const float &angle, const float &x, const float &y, const float &z)
{
  float ar = float(angle*M_PI/180.0f);
  float c = cos(ar);
  float s = sin(ar);

  Matrix4x4 rotation(
        (x*x*(1-c))+c,      (x*y*(1-c))-(z*s),  (x*z*(1-c))+(y*s),  0,
        (x*y*(1-c))+(z*s),  (y*y*(1-c))+c,      (y*z*(1-c))-(x*s),  0,
        (x*z*(1-c))-(y*s),  (y*z*(1-c))+(x*s),  (z*z*(1-c))+c,      0,
        0,                  0,                  0,                  1
        );

  *this = (*this)*rotation;
}

void Matrix4x4::rotateX(const float &angle)
{
  rotate(angle,1.0f,0.0f,0.0f);
}

void Matrix4x4::rotateY(const float &angle)
{
  rotate(angle,0.0f,1.0f,0.0f);
}

void Matrix4x4::rotateZ(const float &angle)
{
  rotate(angle,0.0f,0.0f,1.0f);
}

void Matrix4x4::translate(const float &x, const float &y, const float &z)
{
  Matrix4x4 translation(
        1.f, 0.f, 0.f, x,
        0.f, 1.f, 0.f, y,
        0.f, 0.f, 1.f, z,
        0.f, 0.f, 0.f, 1.f
        );
  *this = (*this)*translation;
}

void Matrix4x4::scale(const float &s)
{
  scale(s,s,s);
}

void Matrix4x4::scale(const float &x, const float &y, const float &z)
{
  Matrix4x4 scaled(
        x, 0.f, 0.f, 0.f,
        0.f, y, 0.f, 0.f,
        0.f, 0.f, z, 0.f,
        0.f, 0.f, 0.f, 1.f
        );
  *this = (*this)*scaled;
}

void Matrix4x4::ortho(const float &left, const float &right, const float &bottom, const float &top, const float &near, const float &far)
{
  float tx = -((right+left)/(right-left));
  float ty = -((top+bottom)/(top-bottom));
  float tz = -((far+near)/(far-near));
  float sx = 2/(right-left);
  float sy = 2/(top-bottom);
  float sz = -2/(far-near);

  Matrix4x4 orthomatrix(
        sx, 0.f, 0.f, tx,
        0.f, sy, 0.f, ty,
        0.f, 0.f, sz, tz,
        0.f, 0.f,  0.f,  1.f
        );
  *this = (*this)*orthomatrix;
}

void Matrix4x4::frustum(const float &left, const float &right, const float &bottom, const float &top, const float &near, const float &far)
{
  float m11 = (2*near)/(right-left);
  float m22 = (2*near)/(top-bottom);
  float m33 = -(far+near)/(far-near);
  float m13 = (right+left)/(right-left);
  float m23 = (top+bottom)/(top-bottom);
  float m34 = (-2*far*near)/(far-near);
  float m43 = -1;

  Matrix4x4 frustummatrix(
        m11, 0.f, m13, 0.f,
        0.f, m22, m23, 0.f,
        0.f, 0.f, m33, m34,
        0.f, 0.f, m43, 0.f
        );
  *this = (*this)*frustummatrix;
}

void Matrix4x4::orthoC(const float &left, const float &right, const float &bottom, const float &top, const float &near, const float &far)
{
  float tx = -((right+left)/(right-left));
  float ty = -((top+bottom)/(top-bottom));
  float tz = ((far+near)/(far-near));
  float sx = 2/(right-left);
  float sy = 2/(top-bottom);
  float sz = 2/(far-near);

  Matrix4x4 orthomatrix(
        sx, 0.f, 0.f, tx,
        0.f, sy, 0.f, ty,
        0.f, 0.f, sz, tz,
        0.f, 0.f,  0.f,  1.f
        );
  *this = (*this)*orthomatrix;
}

void Matrix4x4::frustumC(const float &left, const float &right, const float &bottom, const float &top, const float &near, const float &far)
{
  float m11 = (2*near)/(right-left);
  float m22 = (2*near)/(top-bottom);
  float m33 = (far+near)/(far-near);
  float m13 = (right+left)/(right-left);
  float m23 = (top+bottom)/(top-bottom);
  float m34 = (2*far*near)/(far-near);
  float m43 = -1;

  Matrix4x4 frustummatrix(
        m11, 0.f, m13, 0.f,
        0.f, m22, m23, 0.f,
        0.f, 0.f, m33, m34,
        0.f, 0.f, m43, 0.f
        );
  *this = (*this)*frustummatrix;
}

void Matrix4x4::transpose()
{
  for(int i=0;i<4;i++){
    for(int j=i+1;j<4;j++){
      float d = data(i,j);
      setData(i,j, data(j,i));
      setData(j,i, d);
    }
  }
}

Matrix4x4 Matrix4x4::transposed() const
{
  Matrix4x4 res = *this;
  res.transpose();
  return res;
}

void Matrix4x4::inverse()
{
  float inv[16], det;
  int i;

  inv[0] = data_[5]  * data_[10] * data_[15] -
           data_[5]  * data_[11] * data_[14] -
           data_[9]  * data_[6]  * data_[15] +
           data_[9]  * data_[7]  * data_[14] +
           data_[13] * data_[6]  * data_[11] -
           data_[13] * data_[7]  * data_[10];

  inv[4] = -data_[4]  * data_[10] * data_[15] +
           data_[4]  * data_[11] * data_[14] +
           data_[8]  * data_[6]  * data_[15] -
           data_[8]  * data_[7]  * data_[14] -
           data_[12] * data_[6]  * data_[11] +
           data_[12] * data_[7]  * data_[10];

  inv[8] = data_[4]  * data_[9] * data_[15] -
           data_[4]  * data_[11] * data_[13] -
           data_[8]  * data_[5] * data_[15] +
           data_[8]  * data_[7] * data_[13] +
           data_[12] * data_[5] * data_[11] -
           data_[12] * data_[7] * data_[9];

  inv[12] = -data_[4]  * data_[9] * data_[14] +
            data_[4]  * data_[10] * data_[13] +
            data_[8]  * data_[5] * data_[14] -
            data_[8]  * data_[6] * data_[13] -
            data_[12] * data_[5] * data_[10] +
            data_[12] * data_[6] * data_[9];

  inv[1] = -data_[1]  * data_[10] * data_[15] +
           data_[1]  * data_[11] * data_[14] +
           data_[9]  * data_[2] * data_[15] -
           data_[9]  * data_[3] * data_[14] -
           data_[13] * data_[2] * data_[11] +
           data_[13] * data_[3] * data_[10];

  inv[5] = data_[0]  * data_[10] * data_[15] -
           data_[0]  * data_[11] * data_[14] -
           data_[8]  * data_[2] * data_[15] +
           data_[8]  * data_[3] * data_[14] +
           data_[12] * data_[2] * data_[11] -
           data_[12] * data_[3] * data_[10];

  inv[9] = -data_[0]  * data_[9] * data_[15] +
           data_[0]  * data_[11] * data_[13] +
           data_[8]  * data_[1] * data_[15] -
           data_[8]  * data_[3] * data_[13] -
           data_[12] * data_[1] * data_[11] +
           data_[12] * data_[3] * data_[9];

  inv[13] = data_[0]  * data_[9] * data_[14] -
            data_[0]  * data_[10] * data_[13] -
            data_[8]  * data_[1] * data_[14] +
            data_[8]  * data_[2] * data_[13] +
            data_[12] * data_[1] * data_[10] -
            data_[12] * data_[2] * data_[9];

  inv[2] = data_[1]  * data_[6] * data_[15] -
           data_[1]  * data_[7] * data_[14] -
           data_[5]  * data_[2] * data_[15] +
           data_[5]  * data_[3] * data_[14] +
           data_[13] * data_[2] * data_[7] -
           data_[13] * data_[3] * data_[6];

  inv[6] = -data_[0]  * data_[6] * data_[15] +
           data_[0]  * data_[7] * data_[14] +
           data_[4]  * data_[2] * data_[15] -
           data_[4]  * data_[3] * data_[14] -
           data_[12] * data_[2] * data_[7] +
           data_[12] * data_[3] * data_[6];

  inv[10] = data_[0]  * data_[5] * data_[15] -
            data_[0]  * data_[7] * data_[13] -
            data_[4]  * data_[1] * data_[15] +
            data_[4]  * data_[3] * data_[13] +
            data_[12] * data_[1] * data_[7] -
            data_[12] * data_[3] * data_[5];

  inv[14] = -data_[0]  * data_[5] * data_[14] +
            data_[0]  * data_[6] * data_[13] +
            data_[4]  * data_[1] * data_[14] -
            data_[4]  * data_[2] * data_[13] -
            data_[12] * data_[1] * data_[6] +
            data_[12] * data_[2] * data_[5];

  inv[3] = -data_[1] * data_[6] * data_[11] +
           data_[1] * data_[7] * data_[10] +
           data_[5] * data_[2] * data_[11] -
           data_[5] * data_[3] * data_[10] -
           data_[9] * data_[2] * data_[7] +
           data_[9] * data_[3] * data_[6];

  inv[7] = data_[0] * data_[6] * data_[11] -
           data_[0] * data_[7] * data_[10] -
           data_[4] * data_[2] * data_[11] +
           data_[4] * data_[3] * data_[10] +
           data_[8] * data_[2] * data_[7] -
           data_[8] * data_[3] * data_[6];

  inv[11] = -data_[0] * data_[5] * data_[11] +
            data_[0] * data_[7] * data_[9] +
            data_[4] * data_[1] * data_[11] -
            data_[4] * data_[3] * data_[9] -
            data_[8] * data_[1] * data_[7] +
            data_[8] * data_[3] * data_[5];

  inv[15] = data_[0] * data_[5] * data_[10] -
            data_[0] * data_[6] * data_[9] -
            data_[4] * data_[1] * data_[10] +
            data_[4] * data_[2] * data_[9] +
            data_[8] * data_[1] * data_[6] -
            data_[8] * data_[2] * data_[5];

  det = data_[0] * inv[0] + data_[1] * inv[4] + data_[2] * inv[8] + data_[3] * inv[12];

  if (det == 0){
    error_ = true;
    return;
  }

  det = 1.0f / det;

  for (i = 0; i < 16; i++)
    data_[i] = inv[i] * det;
}

Matrix4x4 Matrix4x4::inverted() const
{
  Matrix4x4 res = *this;
  res.inverse();
  return res;
}

std::ostream &operator<<(std::ostream &os, const Matrix4x4 &dt)
{
  os << ""<<dt.data(0,0)<<"\t"<<dt.data(0,1)<<"\t"<<dt.data(0,2)<<"\t"<<dt.data(0,3)<<"\n";
  os << ""<<dt.data(1,0)<<"\t"<<dt.data(1,1)<<"\t"<<dt.data(1,2)<<"\t"<<dt.data(1,3)<<"\n";
  os << ""<<dt.data(2,0)<<"\t"<<dt.data(2,1)<<"\t"<<dt.data(2,2)<<"\t"<<dt.data(2,3)<<"\n";
  os << ""<<dt.data(3,0)<<"\t"<<dt.data(3,1)<<"\t"<<dt.data(3,2)<<"\t"<<dt.data(3,3)<<"";
  return os;
}

Matrix4x4 operator*(const Matrix4x4 &m1, const Matrix4x4 &m2)
{
  Matrix4x4 result;
  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
      result.setData(i,j, 0.0f);
      for(int k=0;k<4;k++){
        result.addData(i,j, m1.data(i,k) * m2.data(k,j));
      }
    }
  }

  return result;
}

Vector4 operator*(const Matrix4x4 &m1, const Vector4 &v2)
{
  Vector4 result;

  for(int i=0;i<4;i++){
    result.setData(i, 0.0f);
    for(int k=0;k<4;k++){
      result.addData(i, m1.data(i,k)*v2.data(k));
    }
  }

  if(result.w()!=0 && result.w()!=1){
    result.setPoint(result.x()/result.w(),
                    result.y()/result.w(),
                    result.z()/result.w());
  }

  return result;
}

}
