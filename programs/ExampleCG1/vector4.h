/*
 * 4D Vector Class by Ricardo Bustamante de Queiroz
 * e-mail: ricardobqueiroz@gmail.com
 */

#ifndef VECTOR4_H
#define VECTOR4_H

#include <ostream>

class Matrix4x4;

class Vector4
{
public:
  Vector4();
  Vector4(const Vector4 &v);
  Vector4(float x, float y, float z, float w);

  void setData(const int &i, const float &value);
  void addData(const int &i, const float &value);
  float data(const int i) const;
  const float *data() const;

  void setPoint(float x, float y, float z);
  void setVector(float x, float y, float z);

  float x() const;
  float y() const;
  float z() const;
  float w() const;

  Vector4 operator=(const Vector4 &v);
private:
  float data_[4];
};

std::ostream &operator<<(std::ostream& os, const Vector4& dt);
Vector4 operator+(const Vector4 &v1, const Vector4 &v2);
Vector4 operator*(const Vector4 &v1, const Matrix4x4 &m2);

#endif // VECTOR4_H
