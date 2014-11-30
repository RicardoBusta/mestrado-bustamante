#ifndef MARCHINGCUBES_H
#define MARCHINGCUBES_H

#include "data/volumedata.h"
//#include "busta_libs/opencl_manager/openclmanager.h"

class MarchingCubes
{
public:
  QVector<QVector3D> march(const VolumeData &data, const float iso_level);
  void setup();
  void release();

  static MarchingCubes * instance();
private:

  QVector3D calculate_vertex(float iso_level, const QPair<float, QVector3D> &vertex1, const QPair<float, QVector3D> &vertex2);
  MarchingCubes();

  static MarchingCubes * instance_;

//  cl_command_queue command_queue_;
//  cl_program program_;
//  cl_kernel kernel_;

//  Busta::OpenCLManager *cl_;

  bool setup_;
};

#endif // MARCHINGCUBES_H
