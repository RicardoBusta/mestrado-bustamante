#include "marchingcubes.h"

const int voxel_size = 10;

#include <QDebug>

#include "busta_libs/opencl_manager/openclmanager.h"

QVector<QVector3D> MarchingCubes::march(const VolumeData &data, const float value)
{
  QVector<QVector3D> output;

  qDebug() << "marching";

  Busta::OpenCLManager *ocl = Busta::OpenCLManager::instance();

  if(ocl==NULL){
    qWarning() << "Could not create instance of OpenCLManager";
    return output;
  }

  ocl->SetupGPUDevice();

  //http://www.heterogeneouscompute.org/wordpress/wp-content/uploads/2011/06/Chapter2.txt

  cl_mem data_buffer;
  cl_mem out_buffer;
  cl_int status;

  //data_buffer = ocl->clCreateBuffer(ocl->GPUContext(),CL_MEM_READ_ONLY,data.data_.size(),NULL,status);
  //out_buffer = ocl->clCreateBuffer(ocl->GPUContext(),CL_MEM_WRITE_ONLY,data.data_.size(),NULL,status);

  //ocl->clReleaseMemObject(data_buffer);


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
