#include "marchingcubes.h"

const int voxel_size = 10;

#include <QDebug>

#include "marchingcubeskernel.h"

MarchingCubes * MarchingCubes::instance_ = NULL;

MarchingCubes::MarchingCubes():
  setup_(false),
  cl_(NULL)
{

}

QVector<QVector3D> MarchingCubes::march(const VolumeData &data, const float value)
{  
  QVector<QVector3D> output;

  setup();

  if(!setup_ || cl_==NULL) return output;

  qDebug() << "marching";

  //http://www.heterogeneouscompute.org/wordpress/wp-content/uploads/2011/06/Chapter2.txt

  cl_mem in_data_buffer;
  cl_mem out_buffer;
  cl_int status;

  size_t data_size = data.data_.size()*sizeof(float);

  in_data_buffer = cl_->clCreateBuffer(cl_->GPUContext(),CL_MEM_READ_ONLY,data_size,NULL,&status);
  if(status!=CL_SUCCESS){qDebug() << "CL not success";}
  out_buffer = cl_->clCreateBuffer(cl_->GPUContext(),CL_MEM_WRITE_ONLY,data_size,NULL,&status);
  if(status!=CL_SUCCESS){qDebug() << "CL not success";}

  status = cl_->clEnqueueWriteBuffer(command_queue_,in_data_buffer,CL_FALSE,0,data_size,data.data_.data(),0,NULL,NULL);
  if(status!=CL_SUCCESS){qDebug() << "CL not success clEnqueueWriteBuffer";}

  status = cl_->clSetKernelArg(kernel_,0,sizeof(cl_mem),&in_data_buffer);
  if(status!=CL_SUCCESS){qDebug() << "CL not success clSetKernelArg";}
  status = cl_->clSetKernelArg(kernel_,1,sizeof(cl_mem),&out_buffer);
  if(status!=CL_SUCCESS){qDebug() << "CL not success clSetKernelArg";}

  size_t global_work_size[] = {data.data_.size()};
  status = cl_->clEnqueueNDRangeKernel(command_queue_,kernel_,1,NULL,global_work_size,NULL,0,NULL,NULL);
  if(status!=CL_SUCCESS){qDebug() << status << "CL not success clEnqueueNDRangeKernel";}

  std::vector<float> out_read;
  out_read.resize(data.data_.size());
  cl_->clEnqueueReadBuffer(command_queue_,out_buffer,CL_TRUE,0,data_size,out_read.data(),0,NULL,NULL);

  cl_->clReleaseMemObject(in_data_buffer);
  cl_->clReleaseMemObject(out_buffer);

  for(int i=0;i<data.data_.size();i++){
    qDebug() << QString("it: %1 in: %2 out: %3").arg(i).arg(data.data_[i]).arg(out_read[i]);
  }

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

void MarchingCubes::setup()
{
  if(setup_) return;

  qDebug() << "Setting up opencl for MarchingCubes";

  cl_ = Busta::OpenCLManager::instance();

  cl_int status = CL_SUCCESS;

  if(cl_==NULL){
    qWarning() << "Could not get instance of OpenCLManager";
    return;
  }

  cl_->SetupGPUDevice();

  if(cl_->GPUDevices().size()<1){
    qDebug() << "Can't execute any opencl command without devices.";
    return;
  }

  command_queue_ = cl_->clCreateCommandQueue(cl_->GPUContext(),cl_->GPUDevices()[0],0,&status);
  if(status!=CL_SUCCESS){qDebug() << "CL not success clCreateCommandQueue";}

  const char * src = mc33_kernel.c_str();
  program_ = cl_->clCreateProgramWithSource(cl_->GPUContext(),1,&src,NULL,&status);
  if(status!=CL_SUCCESS){qDebug() << "CL not success clCreateProgramWithSource";}

  status = cl_->clBuildProgram(program_,cl_->GPUDevices().size(),cl_->GPUDevices().data(),NULL,NULL,NULL);
  if(status!=CL_SUCCESS){qDebug() << "CL not success clBuildProgram";}

  //===========
  // for debug only
  cl_uint build_info_size;
  status = cl_->clGetProgramBuildInfo(program_,cl_->GPUDevices()[0],CL_PROGRAM_BUILD_LOG,0,NULL,&build_info_size);
  if(status!=CL_SUCCESS){qDebug() << "CL not success clBuildProgram";}

  std::vector<char> build_info;
  build_info.resize(build_info_size);
  status = cl_->clGetProgramBuildInfo(program_,cl_->GPUDevices()[0],CL_PROGRAM_BUILD_LOG,build_info_size,build_info.data(),NULL);
  if(status!=CL_SUCCESS){qDebug() << "CL not success clBuildProgram";}

  if(build_info.size()>0){
    QString build_info_out = QString::fromLatin1(build_info.data());
    qDebug() << "build result:" <<build_info_out.trimmed();
  }
  //===========

  kernel_ = cl_->clCreateKernel(program_,"mc33",&status);
  if(status!=CL_SUCCESS){qDebug() << "CL not success clCreateKernel";}

  setup_ = true;
}

void MarchingCubes::release()
{
  qDebug() << "clearing marching cubes";
  cl_->clReleaseKernel(kernel_);
  cl_->clReleaseProgram(program_);
  cl_->clReleaseCommandQueue(command_queue_);
}

MarchingCubes *MarchingCubes::instance()
{
  if(instance_==NULL){
    instance_ = new MarchingCubes();
  }
  return instance_;
}

int MarchingCubes::pattern(const QVector3D &p1, const QVector3D &p2, const VolumeData &data, const float value)
{
  if(data.getParametricValue(p1.x(),p1.y(),p1.z())>value){
    return 1;
  }
  return 0;
  //data.getParametricValue(p1.x(),p1.y(),p1.z());
}
