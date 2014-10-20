#ifndef MARCHINGCUBES_H
#define MARCHINGCUBES_H

#include "data/volumedata.h"
#include "busta_libs/opencl_manager/openclmanager.h"

class MarchingCubes
{
public:
  QVector<QVector3D> march(const VolumeData &data, const float value);
  void setup();
  void clear();

  static MarchingCubes * instance();
private:

  static int pattern(const QVector3D &p1, const QVector3D &p2, const VolumeData &data, const float value);
  MarchingCubes();

  static MarchingCubes * instance_;

  cl_command_queue command_queue_;
  cl_program program_;
  cl_kernel kernel_;

  Busta::OpenCLManager *cl_;

  bool setup_;
};

#endif // MARCHINGCUBES_H
