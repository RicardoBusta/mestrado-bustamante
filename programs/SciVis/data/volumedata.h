#ifndef VOLUMEDATA_H
#define VOLUMEDATA_H

#include <QVector>

#include <QtOpenGL>

class VolumeData
{
public:
  VolumeData();

  int w,h,d;
  QVector<unsigned short> data_;
  float max_val_;
  float min_val_;

  GLuint texture_id_;

  void setValue(int i, int j, int k, unsigned short value);
  unsigned short getValue(int i, int j, int k, bool print = false) const;
  // float values between 0 and w,h,d
  float getInterpolatedValue(float i, float j, float k, bool print = false) const;
  // float values between 0 and 1
  float getParametricValue(float i, float j, float k, bool print = false) const;
  // float values between 0 and 1, returns value between 0 and 1
  float getNormalizedValues(float i, float j, float k, bool print = false) const;
private:
  int limit(int val, int min, int max) const;
};

#endif // VOLUMEDATA_H
