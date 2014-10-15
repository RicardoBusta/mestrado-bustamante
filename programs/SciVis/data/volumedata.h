#ifndef VOLUMEDATA_H
#define VOLUMEDATA_H

#include <QVector>

class VolumeData
{
public:
  VolumeData();

  int w,h,d;
  QVector<float> data_;
};

#endif // VOLUMEDATA_H
