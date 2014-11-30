#include "volumedata.h"

//#include <QDebug>


#include <limits>

const int kSize = 256;

#include <QFile>

const QRegExp kObjFileNameRegex = QRegExp("ObjectFileName:\\s*(\\S*)");
const QRegExp kResolutionRegex = QRegExp("Resolution:\\s*(\\d+)\\s+(\\d+)\\s+(\\d+)");

VolumeData::VolumeData()
{


  //max_val_ = std::numeric_limits<float>::min();
  //min_val_ = std::numeric_limits<float>::max();



//  w=h=d=kSize;
//  data_.resize(w*h*d);
//  for(int i=0;i<h;i++){
//    //float fi = (float(i)-(float(kSize)/2.0f))/(kSize/2);
//    for(int j=0;j<w;j++){
//      //float fj = (float(j)-(float(kSize)/2.0f))/(kSize/2);
//      for(int k=0;k<d;k++){
//        //float fk = (float(k)-(float(kSize)/2.0f))/(kSize/2);
//        unsigned short val;// = (kSize-sqrt(float((i-kSize/2)*(i-kSize/2)+(j-kSize/2)*(j-kSize/2)+(k-kSize/2)*(k-kSize/2))))*0xff;
//        if(i>kSize/4 && i<3*kSize/4){
//          val = 0x11;
//        }else{
//          val = 0xff;
//        }
//          max_val_ = max_val_>=val?max_val_:val;
//          min_val_ = min_val_<=val?min_val_:val;
//          setValue(i,j,k, val ) ;

//      }
//    }
//  }

//  qDebug() << getNormalizedValues(0.5,0.5,0.5,true);



//  for(int i=0;i<w*d*h;i++){
//    unsigned short val = data_[i];
//    max_val_ = max_val_>=val?max_val_:val;
//    min_val_ = min_val_<=val?min_val_:val;
  //  }
}

void VolumeData::load(QString dat_file_name)
{
  max_val_ = 255;
  min_val_ = 0;

  w = 0;
  h = 0;
  d = 0;

  QString raw_file_name;

  qDebug() << "Attempting to open" << dat_file_name;

  if(dat_file_name=="") return;

  QFile dat_file(dat_file_name);
  if(dat_file.open(QIODevice::ReadOnly|QIODevice::Text)){
    QFileInfo info(dat_file);

    qDebug() << "Dat File Open!" << dat_file.fileName();
    while(!dat_file.atEnd()){
      QString line = dat_file.readLine();
      if(kObjFileNameRegex.indexIn(line)>-1){
        raw_file_name = info.dir().path()+"/"+kObjFileNameRegex.cap(1);
        qDebug() << "file name" << raw_file_name;
      }
      if(kResolutionRegex.indexIn(line)>-1){
        w = kResolutionRegex.cap(1).toInt();
        h = kResolutionRegex.cap(2).toInt();
        d = kResolutionRegex.cap(3).toInt();
        qDebug() << "resolution" << w << h << d;
      }
    }
  }else return;

  qDebug() << "path?" << raw_file_name;

  QFile file(raw_file_name);
  if(file.open(QIODevice::ReadOnly)){
    qDebug() << "File Open!" << file.fileName();
    data_.resize(w*d*h);
    QByteArray data = file.readAll();
    memcpy(data_.data(),data.data(),w*d*h*sizeof(unsigned short));
  }else return;
}

void VolumeData::setValue(int i, int j, int k, unsigned short value)
{
  //qDebug() << "data.size" << data_.size() << "index:" << (i)+(w*j)+(w*h*k);
  data_[(i)+(w*j)+(w*h*k)] = value;
}

unsigned short VolumeData::getValue(int i, int j, int k, bool print) const
{
  if(data_.size()==0) return 0;
  if((i)+(w*j)+(w*h*k) >= data_.size()) return 0;
//  qDebug() << "data.size" << data_.size() << i << j << k << "index:" << (i)+(w*j)+(w*h*k) << data_[(i)+(w*j)+(w*h*k)];
  if(print){
    qDebug() << QString("getValue(%1,%2,%3)").arg(i).arg(j).arg(k) << data_[(i)+(w*j)+(w*h*k)];
  }
  return data_[(i)+(w*j)+(w*h*k)];
}

unsigned short VolumeData::getValue256(int i, int j, int k, bool print) const
{
  float offx = (256.0f - float(h))/2.0f;
  float offy = (256.0f - float(w))/2.0f;
  float offz = (256.0f - float(d))/2.0f;

  if(i<offx || i > 256.0f-offx){
    return 0;
  }
  if(j<offy || j > 256.0f-offy){
    return 0;
  }
  if(k<offz || k > 256.0f-offz){
    return 0;
  }

  if(print){
    qDebug() << "getValue256" << i<<j<<k << offx << offy << offz;
  }

  return getInterpolatedValue(i-offx, j-offy, k-offz,print);
}

unsigned short VolumeData::getValueF(float fi, float fj, float fk, bool print) const
{
  float i = fi*256.0f, j = fj * 256.0f, k = fk*256.0f;

  float offx = (256.0f - float(h))/2.0f;
  float offy = (256.0f - float(w))/2.0f;
  float offz = (256.0f - float(d))/2.0f;

  if(i<offx || i > 256.0f-offx){
    return 0;
  }
  if(j<offy || j > 256.0f-offy){
    return 0;
  }
  if(k<offz || k > 256.0f-offz){
    return 0;
  }

  if(print){
    qDebug() << "getValue256" << i<<j<<k << offx << offy << offz;
  }

  return getInterpolatedValue(i-offx, j-offy, k-offz,print);
}

float VolumeData::getInterpolatedValue(float i, float j, float k, bool print) const
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

  float v000 = getValue(inti,intj,intk,print);
  float v100 = getValue(inti+addi,intj,intk,print);
  float v010 = getValue(inti,intj+addj,intk,print);
  float v110 = getValue(inti+addi,intj+addj,intk,print);
  float v001 = getValue(inti,intj,intk+addk,print);
  float v101 = getValue(inti+addi,intj,intk+addk,print);
  float v011 = getValue(inti,intj+addj,intk+addk,print);
  float v111 = getValue(inti+addi,intj+addj,intk+addk,print);

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

  if(print){
    qDebug() << QString("getInterpolatedValue(%1,%2,%3)").arg(i).arg(j).arg(k) << v;
  }
  return v;
}

float VolumeData::getParametricValue(float i, float j, float k, bool print) const
{
  if(print){
    qDebug() << QString("getParametricValue(%1,%2,%3)").arg(i).arg(j).arg(k) << getInterpolatedValue(i*float(h-1),j*float(w-1),k*float(d-1),print);
  }
  return getInterpolatedValue(i*float(h-1),j*float(w-1),k*float(d-1),print);
}

float VolumeData::getNormalizedValues(float i, float j, float k, bool print) const
{
  float v = getParametricValue(i,j,k,print);
  float res;
  if(max_val_-min_val_!=0){
    res = (v-min_val_)/(max_val_-min_val_);
  }else{
    res = 0;
  }

  if(print){
    qDebug() << QString("getNormalizedValues(%1,%2,%3)").arg(i).arg(j).arg(k)
             << QString("MaxVal(%1) MinVal(%2)").arg(max_val_).arg(min_val_)
             << res;
  }
  return res;
}

int VolumeData::limit(int val, int min, int max) const
{
  return qMin<int>(max,qMax<int>(min,val));
}
