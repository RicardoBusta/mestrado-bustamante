#include "openclmanager.h"

#include <QDebug>

namespace Busta{

  OpenCLManager * OpenCLManager::instance_ = NULL;

#if defined(_WIN32)
#  include <windows.h>
  const std::wstring kClLibName = L"Opencl.dll";
#elif  defined(__GNUC__)
#  include <dlfcn.h>
  const std::string kClLibName = "libOpenCL.so";
#else
#  error Invalid OS
#endif

  OpenCLManager::OpenCLManager():
    lib_(NULL),
    is_enabled_(false),
    bind_error_(false),
    platform_id_func_(NULL),
    platform_info_func_(NULL),
    get_device_ids_func_(NULL),
    get_device_info_func_(NULL),
    create_context_func_(NULL),
    create_context_from_type_func_(NULL),
    retain_context_func_(NULL),
    release_context_func_(NULL),
    get_context_info_func_(NULL),
    create_command_queue_func_(NULL),
    retaing_command_queue_(NULL),
    release_command_queue_func_(NULL),
    get_command_queue_info_func_(NULL),
    set_command_queue_property_func_(NULL),
    create_buffer_func_(NULL),
    create_subbuffer_func_(NULL),
    create_image_2d_func_(NULL),
    create_image_3d_func_(NULL),
    retain_mem_object_func_(NULL),
    release_mem_object_func_(NULL),
    get_mem_object_info_func_(NULL),
    get_image_info_func_(NULL),
    set_mem_object_destructor_callback_func_(NULL),
    create_sampler_func_(NULL),
    retain_sampler_func_(NULL),
    release_sampler_func_(NULL),
    get_sampler_info_func_(NULL),
    create_program_with_source_func_(NULL),
    create_program_with_binary_func_(NULL),
    retain_program_(NULL),
    release_program_func_(NULL),
    build_program_func_(NULL),
    unload_compiler_func_(NULL),
    get_program_info_func_(NULL),
    get_program_build_info_func_(NULL),
    create_kernel_func_(NULL),
    create_kernels_in_program_func_(NULL),
    retain_kernel_func_(NULL),
    release_kernel_func_(NULL),
    set_kerne_arg_func_(NULL),
    get_kernel_info_func_(NULL),
    get_kernel_work_group_info_func_(NULL),
    wait_for_events_func_(NULL),
    get_event_info_func_(NULL),
    retain_event_func_(NULL),
    release_event_func_(NULL),
    set_user_event_status_func_(NULL),
    set_event_callback_func_(NULL),
    get_event_profiling_info_func_(NULL),
    flush_func_(NULL),
    finish_func_(NULL),
    enqueue_read_buffer_func_(NULL),
    enqueue_read_buffer_rect_func_(NULL),
    enqueue_write_buffer_func_(NULL),
    enqueue_write_buffer_rect_func_(NULL),
    enqueue_copy_buffer_func_(NULL),
    enqueue_copy_buffer_rect_func_(NULL),
    enqueue_read_image_func_(NULL),
    enqueue_write_image_func_(NULL),
    enqueue_copy_image_func_(NULL),
    enqueue_copy_image_to_buffer_func_(NULL),
    enqueue_copy_buffer_to_image_func_(NULL),
    enqueue_map_buffer_func_(NULL),
    enqueue_map_image_func_(NULL),
    enqueue_unmap_mem_object_func_(NULL),
    enqueue_nd_range_kernel_func_(NULL),
    enqueue_task_func_(NULL),
    enqueue_native_kernel_func_(NULL),
    enqueue_marker_func_(NULL),
    enqueue_wait_for_events_func_(NULL),
    enqueue_barrier_func_(NULL),
    gpu_devices_(NULL),
    gpu_platform_(0),
    gpu_setup_(false)
  {
  }

  OpenCLManager::~OpenCLManager()
  {
  }

  void * const OpenCLManager::getProcAddr(const char *symbol)
  {
    if(!is_enabled_) return NULL;

#if defined(_WIN32)
    return (void*)GetProcAddress( (HMODULE) lib_, symbol );
#elif defined(__GNUC__)
    char* error = NULL;
    void* addr = NULL;
    dlerror();
    if( NULL != lib_ ){
      addr = dlsym( lib_, symbol );
      error = dlerror();
    }
    if( NULL == error ){
      return addr;
    }else{
      return NULL;
    }
#else
#error Operating system not supported
#endif
  }

  bool OpenCLManager::LoadLib()
  {
    if(is_enabled_) return true;

#if defined(_WIN32)
    lib_ = LoadLibraryW(kClLibName.c_str());
    QString libname = QString::fromStdWString(kClLibName);
#elif defined(__GNUC__)
    lib_ = dlopen(kClLibName.c_str(), RTLD_LAZY);
    QString libname = QString::fromStdString(kClLibName);
#else
#error Operating system not supported
#endif

    if ( NULL == lib_ ) {
      qWarning() << "Failed to load lib: " << libname;
      return false;
    }else{
      is_enabled_ = true;
      //      qWarning() << "Success to load lib: " << libname;
      return true;
    }
  }

  void OpenCLManager::UnloadLibrary()
  {
    if( NULL != lib_ ){
#if defined(_WIN32)
      bool ret = FreeLibrary( (HMODULE)lib_ );
#elif defined(__GNUC__)
      int ret = dlclose( lib_ );
#else
#error Operating system not supported
#endif
      is_enabled_ = false;
      if( 1 != ret ){
        qDebug() << "Failed unloading lib:" << ret;
      }
    }
  }

  void OpenCLManager::SetupGPUDevice()
  {
    if(gpu_setup_) return;

    std::vector<cl_platform_id> platforms;
    std::vector<cl_device_id> devices;

    //--------------------------------
    // Platform related
    //--------------------------------
    cl_uint num_platforms=0;
    if(clGetPlatformIDs(0,NULL,&num_platforms)!=CL_SUCCESS){
      qWarning() << "Not able to query number of platforms.";
    }

    cl_platform_id * platforms_ptr = NULL;
    platforms_ptr = new cl_platform_id[num_platforms];
    platforms.resize(num_platforms);
    if(clGetPlatformIDs(num_platforms,platforms_ptr,NULL)!=CL_SUCCESS){
      qWarning() << "Unable to enumerate platforms.";
      delete platforms_ptr;
      return;
    }
    platforms.assign(platforms_ptr,platforms_ptr+num_platforms);
    delete platforms_ptr;

    //--------------------------------
    // Device related
    //--------------------------------
    for(int i=0;i<platforms.size();i++){
      cl_uint num_devices=0;
      if(clGetDeviceIDs(platforms[i],CL_DEVICE_TYPE_GPU,0,NULL,&num_devices)!=CL_SUCCESS){
        qWarning() << "Failed to get platform devices.";
        continue;
      }

      cl_device_id * devices_ptr = NULL;
      devices_ptr = new cl_device_id[num_devices];
      devices.resize(num_devices);
      if(clGetDeviceIDs(platforms[i],CL_DEVICE_TYPE_GPU,num_devices,devices_ptr,NULL)!=CL_SUCCESS){
        qWarning() << "Failed to enumerate platform devices.";
        delete devices_ptr;
        continue;
      }
      devices.assign(devices_ptr,devices_ptr+num_devices);
      delete devices_ptr;

      if(devices.size()>0){
        gpu_platform_ = platforms[i];
        gpu_devices_ = devices;
        break;
      }
    }

    //--------------------------------
    // Create the context
    //--------------------------------

    cl_int status;
    //delete devices;
    gpu_context_ = clCreateContext(NULL,gpu_devices_.size(),gpu_devices_.data(),NULL,NULL,&status);
    if(status!=CL_SUCCESS){
      qWarning() << "Failed to create the context.";
      return;
    }

    gpu_setup_ = true;
  }

  cl_context OpenCLManager::GPUContext() const
  {
    return gpu_context_;
  }

  std::vector<cl_device_id> OpenCLManager::GPUDevices() const
  {
    return gpu_devices_;
  }

  OpenCLManager *OpenCLManager::instance()
  {
    if(instance_ == NULL){
      instance_ = new OpenCLManager();
    }
    return instance_;
  }

  cl_int OpenCLManager::clGetPlatformIDs( cl_uint num_entries, cl_platform_id * platforms, cl_uint * num_platforms )
  {
    if( platform_id_func_ == NULL ){
      platform_id_func_ = (PF_CL_GET_PLATFORM_IDS) getProcAddr( "clGetPlatformIDs" );
    }

    if( platform_id_func_ != NULL){
      return platform_id_func_(num_entries, platforms, num_platforms );
    }else{
      qWarning() << "Bind Error: platform_id_func_";
      bind_error_ = true;
      return 0;
    }
  }

  cl_int OpenCLManager::clGetDeviceIDs(cl_platform_id platform, cl_device_type device_type, cl_uint num_entries, cl_device_id *devices, cl_uint *num_devices)
  {
    if( get_device_ids_func_ == NULL ){
      get_device_ids_func_ = (PF_CL_GET_DEVICE_IDS) getProcAddr( "clGetDeviceIDs" );
    }

    if( get_device_ids_func_ != NULL){
      return get_device_ids_func_(platform,device_type,num_entries,devices,num_devices);
    }else{
      qWarning() << "Bind Error: get_device_ids_func_";
      bind_error_ = true;
      return 0;
    }
  }

  cl_context OpenCLManager::clCreateContext(const cl_context_properties *properties, cl_uint num_devices, const cl_device_id *devices, void (CL_CALLBACK*pfn_notify)(const char *, const void *, size_t, void *), void *user_data, cl_int *errcode_ret)
  {
    if( create_context_func_ == NULL ){
      create_context_func_ = (PF_CL_CREATE_CONTEXT) getProcAddr( "clCreateContext" );
    }

    if( create_context_func_ != NULL){
      return create_context_func_(properties,num_devices,devices,pfn_notify,user_data,errcode_ret);
    }else{
      qWarning() << "Bind Error: create_context_func_";
      bind_error_ = true;
      return NULL;
    }
  }

  cl_mem OpenCLManager::clCreateBuffer(cl_context context, cl_mem_flags flags, size_t size, void *host_ptr, cl_int *errcode_ret)
  {
    if( create_buffer_func_ == NULL ){
      create_buffer_func_ = (PF_CL_CREATE_BUFFER) getProcAddr( "clCreateBuffer" );
    }

    if( create_buffer_func_ != NULL){
      return create_buffer_func_(context,flags,size,host_ptr,errcode_ret);
    }else{
      qWarning() << "Bind Error: create_buffer_func_";
      bind_error_ = true;
      return NULL;
    }
  }

  cl_int OpenCLManager::clReleaseMemObject(cl_mem memobj)
  {
    if( release_mem_object_func_ == NULL ){
      release_mem_object_func_ = (PF_CL_RELEASE_MEMOBJECT) getProcAddr( "clReleaseMemObject" );
    }

    if( release_mem_object_func_ != NULL){
      return release_mem_object_func_(memobj);
    }else{
      qWarning() << "Bind Error: release_mem_object_func_";
      bind_error_ = true;
      return 0;
    }
  }

}
