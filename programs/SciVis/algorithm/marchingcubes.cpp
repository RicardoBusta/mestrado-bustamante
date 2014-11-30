#include "marchingcubes.h"

const int kVoxelSize = 100;

//#include <QDebug>

//#include "marchingcubeskernel.h"
#include "marchingcubestables.h"

MarchingCubes * MarchingCubes::instance_ = NULL;

MarchingCubes::MarchingCubes():
  setup_(false)
//  cl_(NULL)
{

}

//QVector<QVector3D> MarchingCubes::march(const VolumeData &data, const float value)
//{
//  QVector<QVector3D> output;

//  setup();

//  if(!setup_ || cl_==NULL) return output;

//  qDebug() << "marching";

//  //http://www.heterogeneouscompute.org/wordpress/wp-content/uploads/2011/06/Chapter2.txt

//  cl_mem in_data_buffer;
//  cl_mem out_buffer;
//  cl_int status;

//  size_t data_size = data.data_.size()*sizeof(float);

//  in_data_buffer = cl_->clCreateBuffer(cl_->GPUContext(),CL_MEM_READ_ONLY,data_size,NULL,&status);
//  if(status!=CL_SUCCESS){qDebug() << "CL not success";}
//  out_buffer = cl_->clCreateBuffer(cl_->GPUContext(),CL_MEM_WRITE_ONLY,data_size,NULL,&status);
//  if(status!=CL_SUCCESS){qDebug() << "CL not success";}

//  status = cl_->clEnqueueWriteBuffer(command_queue_,in_data_buffer,CL_FALSE,0,data_size,data.data_.data(),0,NULL,NULL);
//  if(status!=CL_SUCCESS){qDebug() << "CL not success clEnqueueWriteBuffer";}

//  status = cl_->clSetKernelArg(kernel_,0,sizeof(cl_mem),&in_data_buffer);
//  if(status!=CL_SUCCESS){qDebug() << "CL not success clSetKernelArg";}
//  status = cl_->clSetKernelArg(kernel_,1,sizeof(cl_mem),&out_buffer);
//  if(status!=CL_SUCCESS){qDebug() << "CL not success clSetKernelArg";}

//  size_t global_work_size[] = {data.data_.size()};
//  status = cl_->clEnqueueNDRangeKernel(command_queue_,kernel_,1,NULL,global_work_size,NULL,0,NULL,NULL);
//  if(status!=CL_SUCCESS){qDebug() << status << "CL not success clEnqueueNDRangeKernel";}

//  std::vector<float> out_read;
//  out_read.resize(data.data_.size());
//  cl_->clEnqueueReadBuffer(command_queue_,out_buffer,CL_TRUE,0,data_size,out_read.data(),0,NULL,NULL);

//  cl_->clReleaseMemObject(in_data_buffer);
//  cl_->clReleaseMemObject(out_buffer);

//  for(int i=0;i<data.data_.size();i++){
//    qDebug() << QString("it: %1 in: %2 out: %3").arg(i).arg(data.data_[i]).arg(out_read[i]);
//  }

//  float inc = 1.0f/float(voxel_size-1);

//  for(int i=0;i<voxel_size;i++){
//    float fi = float(i)/float(voxel_size-1);
//    for(int j=0;j<voxel_size;j++){
//      float fj = float(j)/float(voxel_size-1);
//      for(int k=0;k<voxel_size;k++){
//        float fk = float(k)/float(voxel_size-1);

//        if( pattern(QVector3D(fi,fj,fk),QVector3D(fi+inc,fj+inc,fk+inc),data,value) == 1 ){
//          output.push_back(QVector3D(fi-1,fj-1,fk-1));
//          output.push_back(QVector3D(+0.5+fi,-0.5+fj,-0.5+fk));
//          output.push_back(QVector3D(+0.5+fi,+0.5+fj,-0.5+fk));

//          output.push_back(QVector3D(-0.5+fi,-0.5+fj,-0.5+fk));
//          output.push_back(QVector3D(+0.5+fi,+0.5+fj,-0.5+fk));
//          output.push_back(QVector3D(-0.5+fi,+0.5+fj,-0.5+fk));
//        }
//      }
//    }
//  }
//  return output;
//}

//void MarchingCubes::setup()
//{
//  if(setup_) return;

//  qDebug() << "Setting up opencl for MarchingCubes";

//  cl_ = Busta::OpenCLManager::instance();

//  cl_int status = CL_SUCCESS;

//  if(cl_==NULL){
//    qWarning() << "Could not get instance of OpenCLManager";
//    return;
//  }

//  cl_->SetupGPUDevice();

//  if(cl_->GPUDevices().size()<1){
//    qDebug() << "Can't execute any opencl command without devices.";
//    return;
//  }

//  command_queue_ = cl_->clCreateCommandQueue(cl_->GPUContext(),cl_->GPUDevices()[0],0,&status);
//  if(status!=CL_SUCCESS){qDebug() << "CL not success clCreateCommandQueue";}

//  const char * src = mc33_kernel.c_str();
//  program_ = cl_->clCreateProgramWithSource(cl_->GPUContext(),1,&src,NULL,&status);
//  if(status!=CL_SUCCESS){qDebug() << "CL not success clCreateProgramWithSource";}

//  status = cl_->clBuildProgram(program_,cl_->GPUDevices().size(),cl_->GPUDevices().data(),NULL,NULL,NULL);
//  if(status!=CL_SUCCESS){qDebug() << "CL not success clBuildProgram";}

//  //===========
//  // for debug only
//  cl_uint build_info_size;
//  status = cl_->clGetProgramBuildInfo(program_,cl_->GPUDevices()[0],CL_PROGRAM_BUILD_LOG,0,NULL,&build_info_size);
//  if(status!=CL_SUCCESS){qDebug() << "CL not success clBuildProgram";}

//  std::vector<char> build_info;
//  build_info.resize(build_info_size);
//  status = cl_->clGetProgramBuildInfo(program_,cl_->GPUDevices()[0],CL_PROGRAM_BUILD_LOG,build_info_size,build_info.data(),NULL);
//  if(status!=CL_SUCCESS){qDebug() << "CL not success clBuildProgram";}

//  if(build_info.size()>0){
//    QString build_info_out = QString::fromLatin1(build_info.data());
//    qDebug() << "build result:" <<build_info_out.trimmed();
//  }
//  //===========

//  kernel_ = cl_->clCreateKernel(program_,"mc33",&status);
//  if(status!=CL_SUCCESS){qDebug() << "CL not success clCreateKernel";}

//  setup_ = true;
//}

//void MarchingCubes::release()
//{
//  qDebug() << "clearing marching cubes";
//  cl_->clReleaseKernel(kernel_);
//  cl_->clReleaseProgram(program_);
//  cl_->clReleaseCommandQueue(command_queue_);
//}

void MarchingCubes::setup()
{

}

void MarchingCubes::release()
{

}

MarchingCubes *MarchingCubes::instance()
{
  if(instance_==NULL){
    instance_ = new MarchingCubes();
  }
  return instance_;
}

QVector3D MarchingCubes::calculate_vertex(float iso_level, const QPair<float, QVector3D> &vertex1, const QPair<float, QVector3D> &vertex2)
{
  if(abs(iso_level-vertex1.first) < 0.0001)
    return vertex1.second;
  if(abs(iso_level-vertex2.first) < 0.0001)
    return vertex2.second;
  if(abs(vertex1.first-vertex2.first) < 0.0001)
    return vertex1.second;
  //Interpolating
  float t = (iso_level-vertex1.first)/(vertex2.first-vertex1.first);
  QVector3D res = vertex1.second + t*(vertex2.second-vertex1.second);
  return res;
}

QVector<QVector3D> MarchingCubes::march(const VolumeData &data, const float iso_level)
{
  QVector<QVector3D> output;

  float div = 1.0f/float(kVoxelSize);

  for(float i=0;i<1.0f;i+=div){
    for(float j=0;j<1.0f;j+=div){
      for(float k=0;k<1.0f;k+=div){
        QVector< QPair<float,QVector3D> > grid;

        // Creating pairs value/points
        grid.push_back(qMakePair(float(data.getValueF(i    ,j    ,k    )),
                                 QVector3D(i    ,j    ,k    )-QVector3D(0.5,0.5,0.5)));
        grid.push_back(qMakePair(float(data.getValueF(i+div,j    ,k    )),
                                 QVector3D(i+div,j    ,k    )-QVector3D(0.5,0.5,0.5)));
        grid.push_back(qMakePair(float(data.getValueF(i+div,j+div,k    )),
                                 QVector3D(i+div,j+div,k    )-QVector3D(0.5,0.5,0.5)));
        grid.push_back(qMakePair(float(data.getValueF(i    ,j+div,k    )),
                                 QVector3D(i    ,j+div,k    )-QVector3D(0.5,0.5,0.5)));
        grid.push_back(qMakePair(float(data.getValueF(i    ,j    ,k+div)),
                                 QVector3D(i    ,j    ,k+div)-QVector3D(0.5,0.5,0.5)));
        grid.push_back(qMakePair(float(data.getValueF(i+div,j    ,k+div)),
                                 QVector3D(i+div,j    ,k+div)-QVector3D(0.5,0.5,0.5)));
        grid.push_back(qMakePair(float(data.getValueF(i+div,j+div,k+div)),
                                 QVector3D(i+div,j+div,k+div)-QVector3D(0.5,0.5,0.5)));
        grid.push_back(qMakePair(float(data.getValueF(i    ,j+div,k+div)),
                                 QVector3D(i    ,j+div,k+div)-QVector3D(0.5,0.5,0.5)));

        unsigned char edge_index = 0;

//        qDebug() << "Marching cubes DEBUG";
//        for(int i=0;i<8;i++){
//          qDebug() << i << grid[i].first;
//        }

        // Calcular o índice do cubo na tabela
        if (grid[0].first < iso_level) edge_index |= 0x01;
        if (grid[1].first < iso_level) edge_index |= 0x02;
        if (grid[2].first < iso_level) edge_index |= 0x04;
        if (grid[3].first < iso_level) edge_index |= 0x08;
        if (grid[4].first < iso_level) edge_index |= 0x10;
        if (grid[5].first < iso_level) edge_index |= 0x20;
        if (grid[6].first < iso_level) edge_index |= 0x40;
        if (grid[7].first < iso_level) edge_index |= 0x80;

//        qDebug() << "edge_index:" << edge_index;

        /* cube empty */
        if(kEdgeTable[edge_index]==0) continue;

        QVector<QVector3D> vertex_list;
        vertex_list.resize(12);

        /* get the vertexes over the surface inside the cube */
        if (kEdgeTable[edge_index] & 1)
          vertex_list[0] = calculate_vertex(iso_level,grid[0],grid[1]);
        if (kEdgeTable[edge_index] & 2)
          vertex_list[1] = calculate_vertex(iso_level,grid[1],grid[2]);
        if (kEdgeTable[edge_index] & 4)
          vertex_list[2] = calculate_vertex(iso_level,grid[2],grid[3]);
        if (kEdgeTable[edge_index] & 8)
          vertex_list[3] = calculate_vertex(iso_level,grid[3],grid[0]);
        if (kEdgeTable[edge_index] & 16)
          vertex_list[4] = calculate_vertex(iso_level,grid[4],grid[5]);
        if (kEdgeTable[edge_index] & 32)
          vertex_list[5] = calculate_vertex(iso_level,grid[5],grid[6]);
        if (kEdgeTable[edge_index] & 64)
          vertex_list[6] = calculate_vertex(iso_level,grid[6],grid[7]);
        if (kEdgeTable[edge_index] & 128)
          vertex_list[7] = calculate_vertex(iso_level,grid[7],grid[4]);
        if (kEdgeTable[edge_index] & 256)
          vertex_list[8] = calculate_vertex(iso_level,grid[0],grid[4]);
        if (kEdgeTable[edge_index] & 512)
          vertex_list[9] = calculate_vertex(iso_level,grid[1],grid[5]);
        if (kEdgeTable[edge_index] & 1024)
          vertex_list[10] = calculate_vertex(iso_level,grid[2],grid[6]);
        if (kEdgeTable[edge_index] & 2048)
          vertex_list[11] = calculate_vertex(iso_level,grid[3],grid[7]);

        for (int i=0;kTriangleTable[edge_index][i]!=-1;i+=3) {
          output.push_back( vertex_list[ kTriangleTable[edge_index][i] ] );
          output.push_back( vertex_list[ kTriangleTable[edge_index][i+1] ] );
          output.push_back( vertex_list[ kTriangleTable[edge_index][i+2] ] );
        }
//        output.push_back(QVector3D(i-0.5f,j-0.5f,k-0.5f));
//        output.push_back(QVector3D(i-0.5f+div,j-0.5f,k-0.5f));
//        output.push_back(QVector3D(i-0.5f+div,j-0.5f+div,k-0.5f));
      }
    }
  }

  qDebug() << "Marching";
  return output;
}
