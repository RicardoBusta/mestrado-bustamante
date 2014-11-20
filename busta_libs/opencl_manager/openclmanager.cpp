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
    qDebug() << "loading lib";
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
      qWarning() << "Success to load lib: " << libname;
      return true;
    }
  }

  void OpenCLManager::UnloadLibrary()
  {
    qDebug() << "unloading lib";
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
      qDebug() << "sucessfully unloaded library";
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

    platforms.resize(num_platforms);
    if(clGetPlatformIDs(num_platforms,platforms.data(),NULL)!=CL_SUCCESS){
      qWarning() << "Unable to enumerate platforms.";
      return;
    }

    //--------------------------------
    // Device related
    //--------------------------------
    for(unsigned int i=0;i<platforms.size();i++){
      cl_uint num_devices=0;
      if(clGetDeviceIDs(platforms[i],CL_DEVICE_TYPE_GPU,0,NULL,&num_devices)!=CL_SUCCESS){
        qWarning() << "Failed to get platform devices.";
        continue;
      }

      devices.resize(num_devices);
      if(clGetDeviceIDs(platforms[i],CL_DEVICE_TYPE_GPU,num_devices,devices.data(),NULL)!=CL_SUCCESS){
        qWarning() << "Failed to enumerate platform devices.";
        continue;
      }

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

  cl_command_queue OpenCLManager::clCreateCommandQueue(cl_context context, cl_device_id device, cl_command_queue_properties properties, cl_int *errcode_ret)
  {
    if( create_command_queue_func_ == NULL ){
      create_command_queue_func_ = (PF_CL_CREATE_COMMAND_QUEUE) getProcAddr( "clCreateCommandQueue" );
    }

    if( create_command_queue_func_ != NULL){
      return create_command_queue_func_(context,device,properties,errcode_ret);
    }else{
      qWarning() << "Bind Error: create_command_queue_func_";
      bind_error_ = true;
      return NULL;
    }
  }

  cl_int OpenCLManager::clReleaseCommandQueue(cl_command_queue command_queue)
  {
    if( release_command_queue_func_ == NULL ){
      release_command_queue_func_ = (PF_CL_RELEASE_COMMAND_QUEUE) getProcAddr( "clReleaseCommandQueue" );
    }

    if( release_command_queue_func_ != NULL){
      return release_command_queue_func_(command_queue);
    }else{
      qWarning() << "Bind Error: release_command_queue_func_";
      bind_error_ = true;
      return 0;
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

  cl_program OpenCLManager::clCreateProgramWithSource(cl_context context, cl_uint count, const char **strings, const size_t *lengths, cl_int *errcode_ret)
  {
    if( create_program_with_source_func_ == NULL ){
      create_program_with_source_func_ = (PF_CL_CREATE_PROGRAM_WITH_SOURCE) getProcAddr( "clCreateProgramWithSource" );
    }

    if( create_program_with_source_func_ != NULL){
      return create_program_with_source_func_(context,count,strings,lengths,errcode_ret);
    }else{
      qWarning() << "Bind Error: create_program_with_source_func_";
      bind_error_ = true;
      return NULL;
    }
  }

  cl_int OpenCLManager::clReleaseProgram(cl_program program)
  {
    if( release_program_func_ == NULL ){
      release_program_func_ = (PF_CL_RELEASE_PROGRAM) getProcAddr( "clReleaseProgram" );
    }

    if( release_program_func_ != NULL){
      return release_program_func_(program);
    }else{
      qWarning() << "Bind Error: release_program_func_";
      bind_error_ = true;
      return 0;
    }
  }

  cl_int OpenCLManager::clBuildProgram(cl_program program, cl_uint num_devices, const cl_device_id *device_list, const char *options, void (CL_CALLBACK*pfn_notify)(cl_program, void *), void *user_data)
  {
    if( build_program_func_ == NULL ){
      build_program_func_ = (PF_CL_BUILD_PROGRAM) getProcAddr( "clBuildProgram" );
    }

    if( build_program_func_ != NULL){
      return build_program_func_(program,num_devices,device_list,options,pfn_notify,user_data);
    }else{
      qWarning() << "Bind Error: enqueue_write_buffer_func_";
      bind_error_ = true;
      return 0;
    }
  }

  cl_int OpenCLManager::clGetProgramBuildInfo(cl_program program, cl_device_id device, cl_program_build_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret)
  {
    if( get_program_build_info_func_ == NULL ){
      get_program_build_info_func_ = (PF_CL_GET_PROGRAM_BUILD_INFO) getProcAddr( "clGetProgramBuildInfo" );
    }

    if( get_program_build_info_func_ != NULL){
      return get_program_build_info_func_(program,device,param_name,param_value_size,param_value,param_value_size_ret);
    }else{
      qWarning() << "Bind Error: get_program_build_info_func_";
      bind_error_ = true;
      return 0;
    }
  }

  cl_kernel OpenCLManager::clCreateKernel(cl_program program, const char *kernel_name, cl_int *errcode_ret)
  {
    if( create_kernel_func_ == NULL ){
      create_kernel_func_ = (PF_CL_CREATE_KERNEL) getProcAddr( "clCreateKernel" );
    }

    if( create_kernel_func_ != NULL){
      return create_kernel_func_(program,kernel_name,errcode_ret);
    }else{
      qWarning() << "Bind Error: create_kernel_func_";
      bind_error_ = true;
      return NULL;
    }
  }

  cl_int OpenCLManager::clReleaseKernel(cl_kernel kernel)
  {
    if( release_kernel_func_ == NULL ){
      release_kernel_func_ = (PF_CL_RELEASE_KERNEL) getProcAddr( "clReleaseKernel" );
    }

    if( release_kernel_func_ != NULL){
      return release_kernel_func_(kernel);
    }else{
      qWarning() << "Bind Error: release_kernel_func_";
      bind_error_ = true;
      return 0;
    }
  }

  cl_int OpenCLManager::clSetKernelArg(cl_kernel kernel, cl_uint arg_index, size_t arg_size, const void *arg_value)
  {
    if( set_kerne_arg_func_ == NULL ){
      set_kerne_arg_func_ = (PF_CL_SET_KERNEL_ARG) getProcAddr( "clSetKernelArg" );
    }

    if( set_kerne_arg_func_ != NULL){
      return set_kerne_arg_func_(kernel,arg_index,arg_size,arg_value);
    }else{
      qWarning() << "Bind Error: set_kerne_arg_func_";
      bind_error_ = true;
      return 0;
    }
  }

  cl_int OpenCLManager::clEnqueueReadBuffer(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, size_t offset, size_t cb, void *ptr, cl_uint num_events_in_wait, const cl_event *event_wait_list, cl_event *event)
  {
    if( enqueue_read_buffer_func_ == NULL ){
      enqueue_read_buffer_func_ = (PF_CL_ENQUEUE_READ_BUFFER) getProcAddr( "clEnqueueReadBuffer" );
    }

    if( enqueue_read_buffer_func_ != NULL){
      return enqueue_read_buffer_func_(command_queue,buffer,blocking_read,offset,cb,ptr,num_events_in_wait,event_wait_list,event);
    }else{
      qWarning() << "Bind Error: enqueue_read_buffer_func_";
      bind_error_ = true;
      return 0;
    }
  }

  cl_int OpenCLManager::clEnqueueWriteBuffer(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, size_t offset, size_t cb, const void *ptr, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event)
  {
    if( enqueue_write_buffer_func_ == NULL ){
      enqueue_write_buffer_func_ = (PF_CL_ENQUEUE_WRITE_BUFFER) getProcAddr( "clEnqueueWriteBuffer" );
    }

    if( enqueue_write_buffer_func_ != NULL){
      return enqueue_write_buffer_func_(command_queue,buffer,blocking_write,offset,cb,ptr,num_events_in_wait_list,event_wait_list,event);
    }else{
      qWarning() << "Bind Error: enqueue_write_buffer_func_";
      bind_error_ = true;
      return 0;
    }
  }

  cl_int OpenCLManager::clEnqueueNDRangeKernel(cl_command_queue command_queue, cl_kernel kernel, cl_uint work_dim, const size_t *global_work_offset, const size_t *global_work_size, const size_t *local_work_size, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event)
  {
    if( enqueue_nd_range_kernel_func_ == NULL ){
      enqueue_nd_range_kernel_func_ = (PF_CL_ENQUEUE_ND_RANGE_KERNEL) getProcAddr( "clEnqueueNDRangeKernel" );
    }

    if( enqueue_nd_range_kernel_func_ != NULL){
      return enqueue_nd_range_kernel_func_(command_queue,kernel,work_dim,global_work_offset,global_work_size,local_work_size,num_events_in_wait_list,event_wait_list,event);
    }else{
      qWarning() << "Bind Error: enqueue_nd_range_kernel_func_";
      bind_error_ = true;
      return 0;
    }
  }

}
