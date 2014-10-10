#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "structures/matrix4x4.h"
#include "structures/vector.h"
#include "structures/color.h"
#include "structures/material.h"

#include <QDebug>

namespace Ric{

Vector operator*(const double &d, const Vector &v);

Vector operator*(const Matrix4x4 &d, const Vector &v);
Vector operator*(const Vector &v, const Matrix4x4 &m);
Matrix4x4 operator*(const Matrix4x4 &m1, const Matrix4x4 &m2);

Vector operator*(const Vector &v, const double &d);
double operator*(const Vector &v1, const Vector &v2);
Vector operator/(const Vector &v, const double &d);
Vector operator^(const Vector &v1, const Vector &v2);
Vector operator+(const Vector &v1, const Vector &v2);
Vector operator+=(Vector &v1, const Vector &v2);
Vector operator-(const Vector &v);
Vector operator-(const Vector &v1, const Vector &v2);

Color operator*(const Color &c, const double &d);
Color operator/(const Color &c, const double &d);
Color operator*(const double &d, const Color &c);
Color operator*(const Color &c1, const Color &c2);
Color operator^(const Color &c, const double &d);
Color operator+(const Color &c1, const Color &c2);
void operator+=(Color &c1, const Color &c2);

QDebug operator<<(QDebug d, const Color &c);
QDebug operator<<(QDebug d, const Vector &v);
QDebug operator<<(QDebug d, const Matrix4x4 &m);
QDebug operator<<(QDebug d, const Material &m);

}

#endif // STRUCTURES_H

