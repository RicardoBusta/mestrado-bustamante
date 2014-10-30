#include "ric.h"

#include <QtGlobal>
#include <QTime>

namespace Ric{
int rand(int a)
{
  return qrand()%a;
}


int rand(int a, int b)
{
  return ((qrand()%(b-a))+a);
}

void init()
{
  qsrand(QTime::currentTime().second());
}

//void MinAndMax(QVector3D &vmin, QVector3D &vmax, const QVector<QVector3D> v)
//{

//}

}
