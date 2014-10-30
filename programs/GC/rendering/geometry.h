#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <QVector3D>
#include <QColor>
#include <QVector>

class QhFace{
public:
  QhFace(const QVector3D &v0, const QVector3D &v1, const QVector3D &v2);
  QhFace(const QVector3D &v0, const QVector3D &v1, const QVector3D &v2, const QColor &color_);
  QhFace(const QVector<QVector3D> &v);
  QhFace(const QVector<QVector3D> &v, const QColor &color);
  QhFace(const QhFace *f);

  void Draw(const float &spread, const float &shrink, const bool user_color) const;
  void DrawTetraFace(const bool user_color) const;
  void SetColor(const QColor &color);

  QhFace operator=(const QhFace &f);
private:
  QVector<QVector3D> v_;
  QVector3D n_;
  QVector3D center_;
  QColor color_;

  bool valid_;
};

class Tetrahedron{
public:
  Tetrahedron(){}
  Tetrahedron(const QVector3D &v0, const QVector3D &v1, const QVector3D &v2);
  Tetrahedron(const QVector3D &v0, const QVector3D &v1, const QVector3D &v2, const QVector3D &v3);
  ~Tetrahedron();

  void Draw(const float &spread, const float &shrink, const bool user_color) const;

  void SetColor(const QColor &color);

  Tetrahedron operator=(const Tetrahedron &t);
private:
  int face_count_;

  QhFace *f[4];
  QVector3D center_;
};

#endif // GEOMETRY_H
