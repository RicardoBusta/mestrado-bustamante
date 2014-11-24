/*
 * 4x4 Matrix Class by Ricardo Bustamante de Queiroz
 * e-mail: ricardobqueiroz@gmail.com
 */

#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include <ostream>

namespace Busta{

class Vector4;

class Matrix4x4
{
public:
  Matrix4x4();
  Matrix4x4(const Matrix4x4 &m);
  Matrix4x4(float m11, float m12, float m13, float m14,
            float m21, float m22, float m23, float m24,
            float m31, float m32, float m33, float m34,
            float m41, float m42, float m43, float m44 );

  bool error() const;

  // Data Manipulation
  void setData(float *data);
  void setData(const int &i, const int &j, const float &value);
  void addData(const int &i, const int &j, const float &value);
  float data(const int &i, const int &j) const;
  const float *data() const;

  // Transform
  void loadIdentity();
  void rotate(const float &angle, const float &x, const float &y, const float &z);
  void rotateX(const float &angle);
  void rotateY(const float &angle);
  void rotateZ(const float &angle);
  void translate(const float &x, const float &y, const float &z);
  void scale(const float &s);
  void scale(const float &x, const float &y, const float &z);
  void ortho(const float &left, const float &right, const float &bottom, const float &top, const float &near, const float &far );
  void frustum(const float &left, const float &right, const float &bottom, const float &top, const float &near, const float &far );
  void orthoC(const float &left, const float &right, const float &bottom, const float &top, const float &near, const float &far );
  void frustumC(const float &left, const float &right, const float &bottom, const float &top, const float &near, const float &far );

  bool isIdentity() const;

  // Matrix Operations
  void transpose();
  Matrix4x4 transposed() const;
  void inverse();
  Matrix4x4 inverted() const;

  Matrix4x4 operator=(const Matrix4x4 &m);
private:
  float data_[16];

  bool error_;
};

std::ostream &operator<<(std::ostream& os, const Matrix4x4& dt);
Matrix4x4 operator*(const Matrix4x4 &m1, const Matrix4x4 &m2);
Vector4 operator*(const Matrix4x4 &m1, const Vector4 &v2);

}

#endif // MATRIX4X4_H
