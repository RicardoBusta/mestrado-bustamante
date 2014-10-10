#include "matrix4x4.h"

#include <cstring>
#include <cmath>

#include "constants.h"
#include "vector.h"

namespace Ric{

  Matrix4x4::Matrix4x4()
  {
    data_[0] = 1; data_[4] = 0; data_[8] = 0; data_[12] = 0;
    data_[1] = 0; data_[5] = 1; data_[9] = 0; data_[13] = 0;
    data_[2] = 0; data_[6] = 0; data_[10] = 1; data_[14] = 0;
    data_[3] = 0; data_[7] = 0; data_[11] = 0; data_[15] = 1;
  }

  Matrix4x4::Matrix4x4(double m11, double m12, double m13, double m14, double m21, double m22, double m23, double m24, double m31, double m32, double m33, double m34, double m41, double m42, double m43, double m44)
  {
    data_[0] = m11; data_[4] = m12; data_[8] = m13; data_[12] = m14;
    data_[1] = m21; data_[5] = m22; data_[9] = m23; data_[13] = m24;
    data_[2] = m31; data_[6] = m32; data_[10] = m33; data_[14] = m34;
    data_[3] = m41; data_[7] = m42; data_[11] = m43; data_[15] = m44;
  }

  Matrix4x4::Matrix4x4(Vector r1, Vector r2, Vector r3)
  {
    data_[0] = r1.x(); data_[4] = r1.y(); data_[8] = r1.z(); data_[12] = 0;
    data_[1] = r2.x(); data_[5] = r2.y(); data_[9] = r2.z(); data_[13] = 0;
    data_[2] = r3.x(); data_[6] = r3.y(); data_[10] = r3.z(); data_[14] = 0;
    data_[3] = 0; data_[7] = 0; data_[11] = 0; data_[15] = 1;
  }

  void Matrix4x4::SetToIdentity()
  {
    data_[0] = 1; data_[4] = 0; data_[8] = 0; data_[12] = 0;
    data_[1] = 0; data_[5] = 1; data_[9] = 0; data_[13] = 0;
    data_[2] = 0; data_[6] = 0; data_[10] = 1; data_[14] = 0;
    data_[3] = 0; data_[7] = 0; data_[11] = 0; data_[15] = 1;
  }

  void Matrix4x4::Ortho(double left, double right, double bottom, double top, double near, double far)
  {
    double tx = -((right+left)/(right-left));
    double ty = -((top+bottom)/(top-bottom));
    double tz = -((far+near)/(far-near));
    double sx = 2/(right-left);
    double sy = 2/(top-bottom);
    double sz = -2/(far-near);

    Matrix4x4 orthomatrix(
          sx, 0, 0, tx,
          0, sy, 0, ty,
          0, 0, sz, tz,
          0, 0,  0,  1
          );
    *this = (*this)*orthomatrix;
  }

  void Matrix4x4::Frustum(double left, double right, double bottom, double top, double near, double far)
  {
    double m11 = (2*near)/(right-left);
    double m22 = (2*near)/(top-bottom);
    double m33 = -(far+near)/(far-near);
    double m13 = (right+left)/(right-left);
    double m23 = (top+bottom)/(top-bottom);
    double m34 = (-2*far*near)/(far-near);
    double m43 = -1;

    Matrix4x4 frustummatrix(
          m11, 0, m13, 0,
          0, m22, m23, 0,
          0, 0, m33, m34,
          0, 0, m43, 0
          );
    *this = (*this)*frustummatrix;
  }

  void Matrix4x4::Rotate(double a, double x, double y, double z)
  {
    double ar = a*M_PI/180.0;
    double c = cos(ar);
    double s = sin(ar);

    Matrix4x4 rotation(
          (x*x*(1-c))+c,      (x*y*(1-c))-(z*s),  (x*z*(1-c))+(y*s),  0,
          (x*y*(1-c))+(z*s),  (y*y*(1-c))+c,      (y*z*(1-c))-(x*s),  0,
          (x*z*(1-c))-(y*s),  (y*z*(1-c))+(x*s),  (z*z*(1-c))+c,      0,
          0,                  0,                  0,                  1
          );

    *this = (*this)*rotation;
  }

  void Matrix4x4::Translate(double x, double y, double z)
  {
    Matrix4x4 translation(
          1, 0, 0, x,
          0, 1, 0, y,
          0, 0, 1, z,
          0, 0, 0, 1
          );
    *this = (*this)*translation;
  }

  void Matrix4x4::Scale(double s)
  {
    Matrix4x4 scaled(
          s, 0, 0, 0,
          0, s, 0, 0,
          0, 0, s, 0,
          0, 0, 0, 1
          );
    *this = (*this)*scaled;
  }

  void Matrix4x4::Scale(double sx, double sy, double sz)
  {
    Matrix4x4 scaled(
          sx, 0, 0,  0,
          0, sy, 0,  0,
          0,  0, sz, 0,
          0,  0, 0,  1
          );
    *this = (*this)*scaled;
  }

  Matrix4x4 Matrix4x4::Inverted() const
  {
    Matrix4x4 out;

    double inv[16], det;
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

    if (det == 0)
      return *this; //false;

    det = 1.0 / det;

    for (i = 0; i < 16; i++)
      out.data_[i] = inv[i] * det;

    return out;// true;
  }

  Matrix4x4 Matrix4x4::Transposed() const
  {
    Matrix4x4 out;
    out.data_[ 0] = data_[ 0]; out.data_[ 1] = data_[ 4]; out.data_[ 2] = data_[ 8]; out.data_[ 3] = data_[12];
    out.data_[ 4] = data_[ 1]; out.data_[ 5] = data_[ 5]; out.data_[ 6] = data_[ 9]; out.data_[ 7] = data_[13];
    out.data_[ 8] = data_[ 2]; out.data_[ 9] = data_[ 6]; out.data_[10] = data_[10]; out.data_[11] = data_[14];
    out.data_[12] = data_[ 3]; out.data_[13] = data_[ 7]; out.data_[14] = data_[11]; out.data_[15] = data_[15];
    return out;
  }

  Matrix4x4 Matrix4x4::operator=(const Matrix4x4 &m2)
  {
    memcpy(this->data_,m2.data_,sizeof(double)*16);
    return *this;
  }

  double Matrix4x4::data(const unsigned int &index) const
  {
    if(index <= 16)
      return data_[index];
    return 0;
  }

  void Matrix4x4::setData(const unsigned int &index, const double &value)
  {
    if(index <= 16)
      data_[index] = value;
  }

} // namespace
