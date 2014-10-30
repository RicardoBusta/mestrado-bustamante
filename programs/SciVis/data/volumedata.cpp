#include "volumedata.h"

//#include <QDebug>

const int kSize = 2;

VolumeData::VolumeData()
{

  w=h=d=kSize;

  data_.resize(w*h*d);

  for(int i=0;i<h;i++){
    float fi = (float(i)-(float(kSize)/2.0f));
    for(int j=0;j<w;j++){
      float fj = (float(j)-(float(kSize)/2.0f));
      for(int k=0;k<d;k++){
        float fk = (float(k)-(float(kSize)/2.0f));
        setValue(i,j,k, (i)+(w*j)+(w*h*k) ) ;
      }
    }
  }
}

void VolumeData::setValue(int i, int j, int k, float value)
{
  data_[(i)+(w*j)+(w*h*k)] = value;
}

float VolumeData::getValue(int i, int j, int k) const
{
  return data_[(i)+(w*j)+(w*h*k)];
}

float VolumeData::getInterpolatedValue(float i, float j, float k) const
{
 float inti = floor(i);
 float intj = floor(j);
 float intk = floor(k);

 //trilinear interpolation

 //TODO: simplify formula

 float vi = i-inti;
 float vj = j-intj;
 float vk = k-intk;

 float v000 = getValue(inti,intj,intk);
 float v100 = getValue(inti+1,intj,intk);
 float v010 = getValue(inti,intj+1,intk);
 float v110 = getValue(inti+1,intj+1,intk);
 float v001 = getValue(inti,intj,intk+1);
 float v101 = getValue(inti+1,intj,intk+1);
 float v011 = getValue(inti,intj+1,intk+1);
 float v111 = getValue(inti+1,intj+1,intk+1);

 //interp i
 float v00 = v000*(1-vi) + v100*vi;
 float v10 = v010*(1-vi) + v110*vi;
 float v11 = v011*(1-vi) + v111*vi;
 float v01 = v001*(1-vi) + v101*vi;

 //interp j
 float v0 = v00*(1-vj) + v01*vj;
 float v1 = v10*(1-vj) + v11*vj;

 //interp k
 float v = v0*(1-vk)+v1*vk;

 return v;
}

float VolumeData::getParametricValue(float i, float j, float k) const
{
  return getInterpolatedValue(i*float(h),j*float(w),k*float(d));
}
