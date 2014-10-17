#ifndef MARCHINGCUBES_H
#define MARCHINGCUBES_H

#include "data/volumedata.h"

class MarchingCubes
{
public:
  static QVector<QVector3D> march(const VolumeData &data, const float value);

private:

  static int pattern(const QVector3D &p1, const QVector3D &p2, const VolumeData &data, const float value);
  MarchingCubes(){}
};

#endif // MARCHINGCUBES_H
