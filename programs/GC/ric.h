#ifndef RANDOM_H
#define RANDOM_H

#include <QVector>
#include <QVector3D>

namespace Ric{
  void init();

  int rand(int a);
  int rand(int a, int b);

//  void MinAndMax(QVector3D &vmin, QVector3D &vmax, const QVector<QVector3D> v);
}

#endif // RANDOM_H

