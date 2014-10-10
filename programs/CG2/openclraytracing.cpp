//#include "openclraytracing.h"

//#include <QDebug>

//OpenClRayTracing::OpenClRayTracing(OpenClLoader *loader)
//{
//  fail_ = false;

//  cl_int err;

//  // +++++++++++++++++++++++++++++++++++++
//  //    IDENTIFY AND GET ONE DEVICE ID
//  // +++++++++++++++++++++++++++++++++++++

//  // First, count how many platforms do we have.
//  cl_uint platform_count = 0;
//  err = loader->clGetPlatformIDs(NULL, NULL, &platform_count);

//  qDebug() << "platform_count: " << platform_count;
//  if( platform_count <= 0 ){
//    fail_ = true;
//    return;
//  }

//  cl_platform_id *platform_ids = new cl_platform_id[platform_count];

//  // Get the IDs of all platforms.
//  err = loader->clGetPlatformIDs(platform_count,platform_ids,NULL);

//  for(cl_uint p=0; p<platform_count;p++){


//    cl_uint device_id_count = 0;
//    err = loader->clGetDeviceIDs(platform_ids[p], CL_DEVICE_TYPE_GPU, NULL, NULL, &device_id_count);

//    qDebug() << "platform: " << p << "device_count" << device_id_count;
//    if( device_id_count <= 0 ){
//      fail_ = true;
//      delete [] platform_ids;
//      return;
//    }

//    cl_device_id * device_ids = new cl_device_id[device_id_count];
//    err = loader->clGetDeviceIDs(platform_ids[p], CL_DEVICE_TYPE_GPU, device_id_count, device_ids, NULL);

//    if( NULL == device_ids[0]){
//      fail_ = true;
//      delete[] device_ids;
//      delete [] platform_ids;
//      return;
//    }

//    device_id_ = device_ids[0];
//    delete[] device_ids;
//  }
//  delete[] platform_ids;

//  // +++++++++++++++++++++++++++++++++++++
//  //    IDENTIFY AND GET ONE DEVICE ID
//  // +++++++++++++++++++++++++++++++++++++


//}
