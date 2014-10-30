#ifndef DELTETRA_H
#define DELTETRA_H

#include <QVector>
#include <QVector3D>
#include <QColor>

class DelTetra
{
public:
  DelTetra();
  DelTetra(const QVector3D &v0, const QVector3D &v1, const QVector3D &v2, const QVector3D &v3, const QColor &color);

  void Draw(const float &spread, const float &shrink, const bool user_color) const;

  QVector3D center_;
  QColor color_;
  QVector<QVector3D> v_;
  QVector<QVector3D> n_;

  DelTetra operator=(const DelTetra &t);

  bool valid_;
};

#endif // DELTETRA_H
