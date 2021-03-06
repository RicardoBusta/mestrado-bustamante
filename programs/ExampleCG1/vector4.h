/*
 * 4D Vector Class by Ricardo Bustamante de Queiroz
 * e-mail: ricardobqueiroz@gmail.com
 */

#ifndef VECTOR4_H
#define VECTOR4_H

#include <QDebug>
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

  float length() const;

  Vector4 normalized() const;

  static Vector4 reflect(const Vector4 &incident, const Vector4 &normal);
  static float dot(const Vector4 &v1, const Vector4 &v2);
  static Vector4 clamp(const Vector4 &v, float min, float max);
  static Vector4 cross(const Vector4 &v1, const Vector4 &v2);
private:
  float data_[4];
};

QDebug operator<<(QDebug os, const Vector4& dt);
std::ostream &operator<<(std::ostream& os, const Vector4& dt);
Vector4 operator+(const Vector4 &v1, const Vector4 &v2);
Vector4 operator-(const Vector4 &v1, const Vector4 &v2);
Vector4 operator-(const Vector4 &v1);
Vector4 operator*(const Vector4 &v1, const Matrix4x4 &m2);
Vector4 operator*(const float &f1, const Vector4 &v2);
Vector4 operator*(const Vector4 &v1, const float &f2);

#endif // VECTOR4_H
