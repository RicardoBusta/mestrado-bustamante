#include "volumedata.h"

//#include <QDebug>


#include <limits>

const int kSize = 256;

VolumeData::VolumeData()
{
  w=h=d=kSize;

  data_.resize(w*h*d);

  max_val_ = std::numeric_limits<float>::min();
  min_val_ = std::numeric_limits<float>::max();

  for(int i=0;i<h;i++){
    float fi = (float(i)-(float(kSize)/2.0f));
    for(int j=0;j<w;j++){
      float fj = (float(j)-(float(kSize)/2.0f));
      for(int k=0;k<d;k++){
        float fk = (float(k)-(float(kSize)/2.0f));
        float val = fi*fi + fj*fj + fk*fk;
        if(val< ((kSize*kSize)/8)){
          val = 1- (val/((kSize*kSize)/8));
          val = val*val*val;
          max_val_ = max_val_>=val?max_val_:val;
          min_val_ = min_val_<=val?min_val_:val;
          setValue(i,j,k, val ) ;
        }else{
          setValue(i,j,k, 0 ) ;
        }
      }
    }
  }
}

void VolumeData::setValue(int i, int j, int k, float value)
{
  //qDebug() << "data.size" << data_.size() << "index:" << (i)+(w*j)+(w*h*k);
  data_[(i)+(w*j)+(w*h*k)] = value;
}

float VolumeData::getValue(int i, int j, int k) const
{
//  qDebug() << "data.size" << data_.size() << i << j << k << "index:" << (i)+(w*j)+(w*h*k) << data_[(i)+(w*j)+(w*h*k)];
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

  int addi = vi==0?0:1;
  int addj = vj==0?0:1;
  int addk = vk==0?0:1;

  float v000 = getValue(inti,intj,intk);
  float v100 = getValue(inti+addi,intj,intk);
  float v010 = getValue(inti,intj+addj,intk);
  float v110 = getValue(inti+addi,intj+addj,intk);
  float v001 = getValue(inti,intj,intk+addk);
  float v101 = getValue(inti+addi,intj,intk+addk);
  float v011 = getValue(inti,intj+addj,intk+addk);
  float v111 = getValue(inti+addi,intj+addj,intk+addk);

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
  return getInterpolatedValue(i*float(h-1),j*float(w-1),k*float(d-1));
}

float VolumeData::getNormalizedValues(float i, float j, float k) const
{
  float v = getParametricValue(i,j,k);
  if(max_val_-min_val_!=0){
    return (v-min_val_)/(max_val_-min_val_);
  }
  return 0;
}

int VolumeData::limit(int val, int min, int max) const
{
  return qMin<int>(max,qMax<int>(min,val));
}
