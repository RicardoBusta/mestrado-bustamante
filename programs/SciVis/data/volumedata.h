#ifndef VOLUMEDATA_H
#define VOLUMEDATA_H

#include <QVector>

#include <QtOpenGL>

class VolumeData
{
public:
  VolumeData();

  int w,h,d;
  QVector<float> data_;

  GLuint texture_id_;

  void setValue(int i, int j, int k, float value);
  float getValue(int i, int j, int k) const;
  float getInterpolatedValue(float i, float j, float k) const;
  float getParametricValue(float i, float j, float k) const;
};

#endif // VOLUMEDATA_H
