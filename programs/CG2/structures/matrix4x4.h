#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include <QVector>

namespace Ric{

  class Vector;
  class Matrix4x4;
  Matrix4x4 operator*(const Matrix4x4 &m1, const Matrix4x4 &m2);

  class Matrix4x4{
  public:
    Matrix4x4();
    Matrix4x4(
        double m11, double m12, double m13, double m14,
        double m21, double m22, double m23, double m24,
        double m31, double m32, double m33, double m34,
        double m41, double m42, double m43, double m44
        );
    Matrix4x4(Ric::Vector r1,Ric::Vector r2,Ric::Vector r3);

    void SetToIdentity();

    // Projection
    void Ortho(double left, double right, double bottom, double top, double near, double far);
    void Frustum(double left, double right, double bottom, double top, double near, double far);

    // Modelview
    void Rotate(double a, double x, double y, double z);
    void Translate(double x, double y, double z);
    void Scale(double s);
    void Scale(double sx,double sy, double sz);

    // Etc
    Matrix4x4 Inverted() const;
    Matrix4x4 Transposed() const;

    Matrix4x4 operator=(const Matrix4x4 &m2);

    double data(const unsigned int &index) const;
    void setData(const unsigned int &index, const double &value);
  private:
    /* 00 04 08 12
   * 01 05 09 13
   * 02 06 10 14
   * 03 07 11 15 */
    double data_[16];
  };

} // namespace

#endif // MATRIX4X4_H
