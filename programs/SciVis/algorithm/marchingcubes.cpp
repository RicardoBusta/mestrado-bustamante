#include "marchingcubes.h"

const int voxel_size = 10;

#include <QDebug>

QVector<QVector3D> MarchingCubes::march(const VolumeData &data, const float value)
{
  QVector<QVector3D> output;

  qDebug() << "marching";

  float inc = 1.0/float(voxel_size-1);

  for(int i=0;i<voxel_size;i++){
    float fi = float(i)/float(voxel_size-1);
    for(int j=0;j<voxel_size;j++){
      float fj = float(j)/float(voxel_size-1);
      for(int k=0;k<voxel_size;k++){
        float fk = float(k)/float(voxel_size-1);

        if( pattern(QVector3D(fi,fj,fk),QVector3D(fi+inc,fj+inc,fk+inc),data,value) == 1 ){
          output.push_back(QVector3D(fi-1,fj-1,fk-1));
          output.push_back(QVector3D(+0.5+fi,-0.5+fj,-0.5+fk));
          output.push_back(QVector3D(+0.5+fi,+0.5+fj,-0.5+fk));

          output.push_back(QVector3D(-0.5+fi,-0.5+fj,-0.5+fk));
          output.push_back(QVector3D(+0.5+fi,+0.5+fj,-0.5+fk));
          output.push_back(QVector3D(-0.5+fi,+0.5+fj,-0.5+fk));
        }
      }
    }
  }

  qDebug() << output.size();

  return output;
}

int MarchingCubes::pattern(const QVector3D &p1, const QVector3D &p2, const VolumeData &data, const float value)
{
  if(data.getParametricValue(p1.x(),p1.y(),p1.z())>value){
    return 1;
  }
  return 0;
  //data.getParametricValue(p1.x(),p1.y(),p1.z());
}
