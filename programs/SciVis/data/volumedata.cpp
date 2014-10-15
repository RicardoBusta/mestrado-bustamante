#include "volumedata.h"

VolumeData::VolumeData()
{
  w=h=d=20;

  data_.resize(w*h*d);

  for(int i=0;i<w;i++){
    for(int j=0;j<h;j++){
      for(int k=0;k<d;k++){
        data_[i+20*j+400*k] = ((i-10)*(i-10) + (j-10)*(j-10) + (k-10)*(k-10))/(3*20*20);
      }
    }
  }
}
