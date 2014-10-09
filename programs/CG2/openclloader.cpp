//#include "openclloader.h"

//#include <QDebug>


//#if defined(_WIN32)
//#include <windows.h>
//const std::wstring kClLibName = L"Opencl.dll";
//#elif  defined(__GNUC__)
//#include <dlfcn.h>
//const std::string kClLibName = "libOpenCL.so";
//#else
//#error Operating system not supported.
//#endif


//OpenClLoader::OpenClLoader()
//  : lib_(NULL),
//    is_enabled_(false)
//{
//  SetNull();
//  LoadLib();
//}

//OpenClLoader::~OpenClLoader()
//{
//  UnloadLibrary();
//  SetNull();
//}

//void OpenClLoader::LoadLib()
//{
//#if defined(_WIN32)
//  lib_ = LoadLibraryW(kClLibName.c_str());
//#elif defined(__GNUC__)
//  lib_ = dlopen(kClLibName.c_str(), RTLD_LAZY);
//#else
//#error Operating system not supported
//#endif

//  if ( NULL == lib_ ) {
//    qDebug() << "Failed to load lib: " << kClLibName.c_str();
//  }else{
//    is_enabled_ = true;
//    qDebug() << "Lib loaded with success: " << kClLibName.c_str();
//  }
//}

//void OpenClLoader::UnloadLibrary()
//{
//  if( NULL != lib_ ){
//#if defined(_WIN32)
//    bool ret = FreeLibrary( (HMODULE)lib_ );
//#elif defined(__GNUC__)
//    int ret = dlclose( lib_ );
//#else
//#error Operating system not supported
//#endif
//    is_enabled_ = false;
//    if( 0 != ret ){
//      qDebug() << "Failed unloading lib:" << ret;
//    }
//  }
//}

//bool OpenClLoader::IsEnabled()
//{
//  return is_enabled_;
//}

//void OpenClLoader::SetNull()
//{
//  platform_id_func_ = NULL;
//  platform_info_func_ = NULL;
//  get_device_ids_func_ = NULL;
//  get_device_info_func_ = NULL;
//  create_context_func_ = NULL;
//  create_context_from_type_func_ = NULL;
//  retain_context_func_ = NULL;
//  release_context_func_ = NULL;
//  get_context_info_func_ = NULL;
//  create_command_queue_func_ = NULL;
//  retaing_command_queue_ = NULL;
//  release_command_queue_func_ = NULL;
//  get_command_queue_info_func_ = NULL;
//  set_command_queue_property_func_ = NULL;
//  create_buffer_func_ = NULL;
//  create_subbuffer_func_ = NULL;
//  create_image_2d_func_ = NULL;
//  create_image_3d_func_ = NULL;
//  retain_mem_object_func_ = NULL;
//  release_mem_object_func_ = NULL;
//  get_mem_object_info_func_ = NULL;
//  get_image_info_func_ = NULL;
//  set_mem_object_destructor_callback_func_ = NULL;
//  create_sampler_func_ = NULL;
//  retain_sampler_func_ = NULL;
//  release_sampler_func_ = NULL;
//  get_sampler_info_func_ = NULL;
//  create_program_with_source_func_ = NULL;
//  create_program_with_binary_func_ = NULL;
//  retain_program_ = NULL;
//  release_program_func_ = NULL;
//  build_program_func_ = NULL;
//  unload_compiler_func_ = NULL;
//  get_program_info_func_ = NULL;
//  get_program_build_info_func_ = NULL;
//  create_kernel_func_ = NULL;
//  create_kernels_in_program_func_ = NULL;
//  retain_kernel_func_ = NULL;
//  release_kernel_func_ = NULL;
//  set_kerne_arg_func_ = NULL;
//  get_kernel_info_func_ = NULL;
//  get_kernel_work_group_info_func_ = NULL;
//  wait_for_events_func_ = NULL;
//  get_event_info_func_ = NULL;
//  retain_event_func_ = NULL;
//  release_event_func_ = NULL;
//  set_user_event_status_func_ = NULL;
//  set_event_callback_func_ = NULL;
//  get_event_profiling_info_func_ = NULL;
//  flush_func_ = NULL;
//  finish_func_ = NULL;
//  enqueue_read_buffer_func_ = NULL;
//  enqueue_read_buffer_rect_func_ = NULL;
//  enqueue_write_buffer_func_ = NULL;
//  enqueue_write_buffer_rect_func_ = NULL;
//  enqueue_copy_buffer_func_ = NULL;
//  enqueue_copy_buffer_rect_func_ = NULL;
//  enqueue_read_image_func_ = NULL;
//  enqueue_write_image_func_ = NULL;
//  enqueue_copy_image_func_ = NULL;
//  enqueue_copy_image_to_buffer_func_ = NULL;
//  enqueue_copy_buffer_to_image_func_ = NULL;
//  enqueue_map_buffer_func_ = NULL;
//  enqueue_map_image_func_ = NULL;
//  enqueue_unmap_mem_object_func_ = NULL;
//  enqueue_nd_range_kernel_func_ = NULL;
//  enqueue_task_func_ = NULL;
//  enqueue_native_kernel_func_ = NULL;
//  enqueue_marker_func_ = NULL;
//  enqueue_wait_for_events_func_ = NULL;
//  enqueue_barrier_func_ = NULL;
//}

//void * const OpenClLoader::getProcAddr( const char * symbol )
//{
//#if defined(_WIN32)
//  return (void*)GetProcAddress( (HMODULE) lib_, symbol );
//#elif defined(__GNUC__)
//  char* error = NULL;
//  void* addr = NULL;
//  dlerror();
//  if( NULL != lib_ ){
//    addr = dlsym( lib_, symbol );
//    error = dlerror();
//  }
//  if( NULL == error ){
//    return addr;
//  }else{
//    return NULL;
//  }
//#else
//#error Operating system not supported
//#endif
//}


//// OpenCL Functions

//cl_int OpenClLoader::clGetPlatformIDs( cl_uint num_entries, cl_platform_id * platforms, cl_uint * num_platforms )
//{
//  if( platform_id_func_ == NULL ){
//    platform_id_func_ = (PF_CL_GET_PLATFORM_IDS) getProcAddr( "clGetPlatformIDs" );
//  }

//  if( platform_id_func_ != NULL){
//    return platform_id_func_(num_entries, platforms, num_platforms );
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_int OpenClLoader::clGetPlatformInfo( cl_platform_id platform, cl_platform_info param_name, size_t param_value_size, void *param_value, size_t * param_value_size_ret )
//{
//  if( platform_info_func_ == NULL ){
//    platform_info_func_ = (PF_CL_GET_PLATFORM_INFO) getProcAddr( "clGetPlatformInfo");
//  }

//  if( platform_info_func_ != NULL){
//    return platform_info_func_(platform, param_name, param_value_size, param_value, param_value_size_ret );
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_int OpenClLoader::clGetDeviceIDs( cl_platform_id platform, cl_device_type device_type, cl_uint num_entries, cl_device_id * devices, cl_uint * num_devices )
//{
//  if( get_device_ids_func_ == NULL ){
//    get_device_ids_func_ = (PF_CL_GET_DEVICE_IDS) getProcAddr( "clGetDeviceIDs");
//  }

//  if( get_device_ids_func_ != NULL){
//    return get_device_ids_func_(platform, device_type, num_entries, devices, num_devices );
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_int OpenClLoader::clGetDeviceInfo( cl_device_id device, cl_device_info param_name, size_t param_value_size, void * param_value, size_t * param_value_size_ret )
//{
//  if( get_device_info_func_ == NULL ){
//    get_device_info_func_ = (PF_CL_GET_DEVICE_INFO) getProcAddr( "clGetDeviceInfo");
//  }

//  if( get_device_info_func_ != NULL){
//    return get_device_info_func_(device, param_name, param_value_size, param_value, param_value_size_ret );
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_context OpenClLoader::clCreateContext(const cl_context_properties * properties, cl_uint num_devices, const cl_device_id * devices, void (CL_CALLBACK * pfn_notify)(const char *, const void *, size_t, void *), void * user_data, cl_int * errcode_ret)
//{
//  if( create_context_func_ == NULL ){
//    create_context_func_ = (PF_CL_CREATE_CONTEXT) getProcAddr( "clCreateContext");
//  }

//  if( create_context_func_ != NULL){
//    return create_context_func_(properties, num_devices, devices, pfn_notify, user_data, errcode_ret );
//  }else{
//    *errcode_ret = OPENCL_FUNCTION_BIND_FAIL;
//    return NULL;
//  }
//}

//cl_context OpenClLoader::clCreateContextFromType(const cl_context_properties *properties, cl_device_type device_type, void (CL_CALLBACK * pfn_notify)(const char *, const void *, size_t, void *), void *user_data, cl_int *errcode_ret)
//{
//  if( create_context_from_type_func_ == NULL ){
//    create_context_from_type_func_ = (PF_CL_CREATE_CONTEXT_FROM_TYPE) getProcAddr( "clCreateContext");
//  }

//  if( create_context_from_type_func_ != NULL){
//    return create_context_from_type_func_(properties, device_type, pfn_notify, user_data, errcode_ret );
//  }else{
//    *errcode_ret = OPENCL_FUNCTION_BIND_FAIL;
//    return NULL;
//  }
//}

//cl_int OpenClLoader::clRetainContext( cl_context context )
//{
//  if( retain_context_func_ == NULL ){
//    retain_context_func_ = (PF_CL_RETAIN_CONTEXT) getProcAddr( "clRetainContext");
//  }

//  if( retain_context_func_ != NULL){
//    return retain_context_func_(context);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_int OpenClLoader::clReleaseContext( cl_context context )
//{
//  if( release_context_func_ == NULL ){
//    release_context_func_ = (PF_CL_RELEASE_CONTEXT) getProcAddr( "clReleaseContext");
//  }

//  if( release_context_func_ != NULL){
//    return release_context_func_(context);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_int OpenClLoader::clGetContextInfo( cl_context context, cl_context_info param_name, size_t param_value_size, void * param_value, size_t *param_value_size_ret )
//{
//  if( get_context_info_func_ == NULL ){
//    get_context_info_func_ = (PF_CL_GET_CONTEXT_INFO) getProcAddr( "clGetContextInfo");
//  }

//  if( get_context_info_func_ != NULL){
//    return get_context_info_func_( context, param_name, param_value_size, param_value, param_value_size_ret );
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_command_queue OpenClLoader::clCreateCommandQueue(cl_context context, cl_device_id device, cl_command_queue_properties properties, cl_int *errcode_ret)
//{
//  if( create_command_queue_func_ == NULL ){
//    create_command_queue_func_ = (PF_CL_CREATE_COMMAND_QUEUE) getProcAddr( "clCreateCommandQueue");
//  }

//  if( create_command_queue_func_ != NULL){
//    return create_command_queue_func_( context, device, properties, errcode_ret);
//  }else{
//    *errcode_ret = OPENCL_FUNCTION_BIND_FAIL;
//    return NULL;
//  }
//}

//cl_mem OpenClLoader::clCreateBuffer(cl_context context, cl_mem_flags flags, size_t size, void *host_ptr, cl_int *errcode_ret)
//{
//  if( create_buffer_func_ == NULL ){
//    create_buffer_func_ = (PF_CL_CREATE_BUFFER) getProcAddr( "clCreateBuffer");
//  }

//  if( create_buffer_func_ != NULL){
//    return create_buffer_func_( context, flags, size, host_ptr, errcode_ret );
//  }else{
//    *errcode_ret = OPENCL_FUNCTION_BIND_FAIL;
//    return NULL;
//  }
//}

//cl_mem OpenClLoader::clCreateSubBuffer(cl_mem buffer, cl_mem_flags flags, cl_buffer_create_type buffer_create_type, const void *buffer_create_info, cl_int *errcode_ret)
//{
//  if( create_subbuffer_func_ == NULL ){
//    create_subbuffer_func_ = (PF_CL_CREATE_SUBBUFFER) getProcAddr( "clCreateSubBuffer");
//  }

//  if( create_subbuffer_func_ != NULL){
//    return create_subbuffer_func_( buffer, flags, buffer_create_type, buffer_create_info, errcode_ret );
//  }else{
//    *errcode_ret = OPENCL_FUNCTION_BIND_FAIL;
//    return NULL;
//  }
//}

//cl_mem OpenClLoader::clCreateImage2D(cl_context context, cl_mem_flags flags, const cl_image_format *image_format, size_t image_width, size_t image_height, size_t image_row_pitch, void *host_ptr, cl_int *errcode_ret)
//{
//  if( create_image_2d_func_ == NULL ){
//    create_image_2d_func_ = (PF_CL_CREATE_IMAGE2D) getProcAddr( "clCreateImage2D");
//  }

//  if( create_image_2d_func_ != NULL){
//    return create_image_2d_func_( context, flags, image_format, image_width, image_height, image_row_pitch, host_ptr, errcode_ret);
//  }else{
//    *errcode_ret = OPENCL_FUNCTION_BIND_FAIL;
//    return NULL;
//  }
//}


//cl_mem OpenClLoader::clCreateImage3D(cl_context context, cl_mem_flags flags, const cl_image_format *image_format, size_t image_width, size_t image_height, size_t image_depth, size_t image_row_pitch, size_t image_slice_pitch, void *host_ptr, cl_int *errcode_ret)
//{
//  if( create_image_3d_func_ == NULL ){
//    create_image_3d_func_ = (PF_CL_CREATE_IMAGE3D) getProcAddr( "clCreateImage3D");
//  }

//  if( create_image_3d_func_ != NULL){
//    return create_image_3d_func_( context, flags, image_format, image_width, image_height, image_depth, image_row_pitch, image_slice_pitch, host_ptr, errcode_ret);
//  }else{
//    *errcode_ret = OPENCL_FUNCTION_BIND_FAIL;
//    return NULL;
//  }
//}


//cl_int OpenClLoader::clRetainMemObject(cl_mem memobj)
//{
//  if( retain_mem_object_func_ == NULL ){
//    retain_mem_object_func_ = (PF_CL_RETAIN_MEMOBJECT) getProcAddr( "clRetainMemObject");
//  }

//  if( retain_mem_object_func_ != NULL){
//    return retain_mem_object_func_(memobj);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}


//cl_int OpenClLoader::clReleaseMemObject(cl_mem memobj)
//{
//  if( release_mem_object_func_ == NULL ){
//    release_mem_object_func_ = (PF_CL_RELEASE_MEMOBJECT) getProcAddr( "clReleaseMemObject");
//  }

//  if( release_mem_object_func_ != NULL){
//    return release_mem_object_func_(memobj);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}


//cl_int OpenClLoader::clGetMemObjectInfo(cl_mem memobj, cl_mem_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret)
//{
//  if( get_mem_object_info_func_ == NULL ){
//    get_mem_object_info_func_ = (PF_CL_GET_MEM_OBJECT_INFO) getProcAddr( "clGetMemObjectInfo");
//  }

//  if( get_mem_object_info_func_ != NULL){
//    return get_mem_object_info_func_(memobj, param_name, param_value_size, param_value, param_value_size_ret);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}


//cl_int OpenClLoader::clGetImageInfo(cl_mem image, cl_image_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret)
//{
//  if( get_image_info_func_ == NULL ){
//    get_image_info_func_ = (PF_CL_GET_IMAGE_INFO) getProcAddr( "clGetImageInfo");
//  }

//  if( get_image_info_func_ != NULL){
//    return get_image_info_func_( image, param_name, param_value_size, param_value, param_value_size_ret );
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_int OpenClLoader::clSetMemObjectDestructorCallback(cl_mem memobj, void (CL_CALLBACK *pfn_notify)(cl_mem, void *), void *user_data)
//{
//  if( set_mem_object_destructor_callback_func_ == NULL ){
//    set_mem_object_destructor_callback_func_ = (PF_CL_SET_MEM_OBJECT_DESTRUCTOR_CALLBACK) getProcAddr( "clSetMemObjectDestructorCallback");
//  }

//  if( set_mem_object_destructor_callback_func_ != NULL){
//    return set_mem_object_destructor_callback_func_( memobj, pfn_notify, user_data);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_sampler OpenClLoader::clCreateSampler(cl_context context, cl_bool normalized_coords, cl_addressing_mode addressing_mode, cl_filter_mode filter_mode, cl_int *errcode_ret)
//{
//  if( create_sampler_func_ == NULL ){
//    create_sampler_func_ = (PF_CL_CREATE_SAMPLER) getProcAddr( "clCreateSampler");
//  }

//  if( create_sampler_func_ != NULL){
//    return create_sampler_func_( context, normalized_coords, addressing_mode, filter_mode, errcode_ret);
//  }else{
//    *errcode_ret = OPENCL_FUNCTION_BIND_FAIL;
//    return NULL;
//  }
//}

//cl_int OpenClLoader::clRetainSampler(cl_sampler sampler)
//{
//  if( retain_sampler_func_ == NULL ){
//    retain_sampler_func_ = (PF_CL_RETAIN_SAMPLER) getProcAddr( "clRetainSampler");
//  }

//  if( retain_sampler_func_ != NULL){
//    return retain_sampler_func_(sampler);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_int OpenClLoader::clReleaseSampler(cl_sampler sampler)
//{
//  if( release_sampler_func_ == NULL ){
//    release_sampler_func_ = (PF_CL_RELEASE_SAMPLER) getProcAddr( "clReleaseSampler");
//  }

//  if( release_sampler_func_ != NULL){
//    return release_sampler_func_(sampler);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_int OpenClLoader::clGetSamplerInfo(cl_sampler sampler, cl_sampler_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret)
//{
//  if( get_sampler_info_func_ == NULL ){
//    get_sampler_info_func_ = (PF_CL_GET_SAMPLER_INFO) getProcAddr( "clGetSamplerInfo");
//  }

//  if( get_sampler_info_func_ != NULL){
//    return get_sampler_info_func_( sampler, param_name, param_value_size, param_value, param_value_size_ret);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_program OpenClLoader::clCreateProgramWithSource(cl_context context, cl_uint count, const char **strings, const size_t *lengths, cl_int *errcode_ret)
//{
//  if( create_program_with_source_func_ == NULL ){
//    create_program_with_source_func_ = (PF_CL_CREATE_PROGRAM_WITH_SOURCE) getProcAddr( "clCreateProgramWithSource");
//  }

//  if( create_program_with_source_func_ != NULL ){
//    return create_program_with_source_func_( context, count, strings, lengths, errcode_ret);
//  }else{
//    *errcode_ret = OPENCL_FUNCTION_BIND_FAIL;
//    return NULL;
//  }
//}


//cl_program OpenClLoader::clCreateProgramWithBinary(cl_context context, cl_uint num_devices, const cl_device_id *device_list, const size_t *lengths, const unsigned char **binaries, cl_int *binary_status, cl_int *errcode_ret)
//{
//  if( create_program_with_binary_func_ == NULL ){
//    create_program_with_binary_func_ = (PF_CL_CREATE_PROGRAM_WITH_BINARY) getProcAddr( "clCreateProgramWithBinary");
//  }

//  if( create_program_with_binary_func_ != NULL){
//    return create_program_with_binary_func_( context, num_devices, device_list, lengths, binaries, binary_status, errcode_ret);
//  }else{
//    *errcode_ret = OPENCL_FUNCTION_BIND_FAIL;
//    return NULL;
//  }
//}

//cl_int OpenClLoader::clRetainProgram(cl_program program)
//{
//  if( retain_program_ == NULL ){
//    retain_program_ = (PF_CL_RETAIN_PROGRAM) getProcAddr( "clRetainProgram");
//  }

//  if( retain_program_ != NULL){
//    return retain_program_(program);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}


//cl_int OpenClLoader::clReleaseProgram(cl_program program)
//{
//  if( release_program_func_ == NULL ){
//    release_program_func_ = (PF_CL_RELEASE_PROGRAM) getProcAddr( "clReleaseProgram");
//  }

//  if( release_program_func_ != NULL){
//    return release_program_func_(program);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_int OpenClLoader::clBuildProgram(cl_program program, cl_uint num_devices, const cl_device_id * device_list, const char * options, void (CL_CALLBACK * pfn_notify)(cl_program, void *), void * user_data)
//{
//  if( build_program_func_ == NULL ){
//    build_program_func_ = (PF_CL_BUILD_PROGRAM) getProcAddr( "clBuildProgram");
//  }
//  if( build_program_func_ != NULL){
//    return build_program_func_( program, num_devices, device_list, options, pfn_notify,user_data);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}


//cl_int OpenClLoader::clUnloadCompiler(void)
//{
//  if( unload_compiler_func_ == NULL ){
//    unload_compiler_func_ = (PF_CL_UNLOAD_COMPILER) getProcAddr( "clUnloadCompiler");
//  }

//  if( unload_compiler_func_ != NULL){
//    return unload_compiler_func_();
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_int OpenClLoader::clGetProgramInfo(cl_program program, cl_program_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret)
//{
//  if( get_program_info_func_ == NULL ){
//    get_program_info_func_ = (PF_CL_GET_PROGRAM_INFO) getProcAddr( "clGetProgramInfo");
//  }

//  if( get_program_info_func_ != NULL){
//    return get_program_info_func_( program, param_name, param_value_size, param_value, param_value_size_ret);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}


//cl_int OpenClLoader::clGetProgramBuildInfo(cl_program program, cl_device_id device, cl_program_build_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret)
//{
//  if( get_program_build_info_func_ == NULL ){
//    get_program_build_info_func_ = (PF_CL_GET_PROGRAM_BUILD_INFO) getProcAddr( "clGetProgramBuildInfo");
//  }

//  if( get_program_build_info_func_ != NULL){
//    return get_program_build_info_func_( program, device, param_name, param_value_size, param_value, param_value_size_ret);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}


//cl_kernel OpenClLoader::clCreateKernel(cl_program program, const char *kernel_name, cl_int *errcode_ret)
//{
//  if( create_kernel_func_ == NULL ){
//    create_kernel_func_ = (PF_CL_CREATE_KERNEL) getProcAddr( "clCreateKernel");
//  }

//  if( create_kernel_func_ != NULL){
//    return create_kernel_func_( program, kernel_name, errcode_ret);
//  }else{
//    *errcode_ret = OPENCL_FUNCTION_BIND_FAIL;
//    return NULL;
//  }
//}


//cl_int OpenClLoader::clCreateKernelsInProgram(cl_program program, cl_uint num_kernels, cl_kernel *kernels, cl_uint *num_kernels_ret)
//{
//  if( create_kernels_in_program_func_ == NULL ){
//    create_kernels_in_program_func_ = (PF_CL_CREATE_KERNELS_IN_PROGRAM) getProcAddr( "clCreateKernelsInProgram");
//  }

//  if( create_kernels_in_program_func_ != NULL){
//    return create_kernels_in_program_func_( program, num_kernels, kernels, num_kernels_ret);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}


//cl_int OpenClLoader::clRetainKernel(cl_kernel kernel)
//{
//  if( retain_kernel_func_ == NULL ){
//    retain_kernel_func_ = (PF_CL_RETAIN_KERNEL) getProcAddr( "clRetainKernel");
//  }

//  if( retain_kernel_func_ != NULL){
//    return retain_kernel_func_(kernel);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}


//cl_int OpenClLoader::clReleaseKernel(cl_kernel kernel)
//{
//  if( release_kernel_func_ == NULL ){
//    release_kernel_func_ = (PF_CL_RELEASE_KERNEL) getProcAddr( "clReleaseKernel");
//  }

//  if( release_kernel_func_ != NULL){
//    return release_kernel_func_(kernel);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}


//cl_int OpenClLoader::clSetKernelArg(cl_kernel kernel, cl_uint arg_index, size_t arg_size, const void *arg_value)
//{
//  if( set_kerne_arg_func_ == NULL ){
//    set_kerne_arg_func_ = (PF_CL_SET_KERNEL_ARG) getProcAddr( "clSetKernelArg");
//  }

//  if( set_kerne_arg_func_ != NULL){
//    return set_kerne_arg_func_( kernel, arg_index, arg_size, arg_value);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}


//cl_int OpenClLoader::clGetKernelInfo(cl_kernel kernel, cl_kernel_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret)
//{
//  if( get_kernel_info_func_ == NULL ){
//    get_kernel_info_func_ = (PF_CL_GET_KERNEL_INFO) getProcAddr( "clGetKernelInfo");
//  }

//  if( get_kernel_info_func_ != NULL){
//    return get_kernel_info_func_( kernel, param_name, param_value_size, param_value, param_value_size_ret);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}


//cl_int OpenClLoader::clGetKernelWorkGroupInfo(cl_kernel kernel, cl_device_id device, cl_kernel_work_group_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret)
//{
//  if( get_kernel_work_group_info_func_ == NULL ){
//    get_kernel_work_group_info_func_ = (PF_CL_GET_KERNEL_WORK_GROUP_INFO) getProcAddr( "clGetKernelWorkGroupInfo");
//  }

//  if( get_kernel_work_group_info_func_ != NULL){
//    return get_kernel_work_group_info_func_( kernel, device, param_name, param_value_size, param_value, param_value_size_ret);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}


//cl_int OpenClLoader::clWaitForEvents(cl_uint num_events, const cl_event *event_list)
//{
//  if( wait_for_events_func_ == NULL ){
//    wait_for_events_func_ = (PF_CL_WAIT_FOR_EVENTS) getProcAddr( "clWaitForEvents");
//  }

//  if( wait_for_events_func_ != NULL){
//    return wait_for_events_func_( num_events, event_list );
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}


//cl_int OpenClLoader::clGetEventInfo(cl_event event, cl_event_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret)
//{
//  if( get_event_info_func_ == NULL ){
//    get_event_info_func_ = (PF_CL_GET_EVENT_INFO) getProcAddr( "clGetEventInfo");
//  }

//  if( get_event_info_func_ != NULL){
//    return get_event_info_func_( event, param_name, param_value_size, param_value, param_value_size_ret);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}


//cl_int OpenClLoader::clRetainEvent(cl_event event)
//{
//  if( retain_event_func_ == NULL ){
//    retain_event_func_ = (PF_CL_RETAIN_EVENT) getProcAddr( "clRetainEvent");
//  }

//  if( retain_event_func_ != NULL){
//    return retain_event_func_(event);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}


//cl_int OpenClLoader::clReleaseEvent(cl_event event)
//{
//  if( release_event_func_ == NULL ){
//    release_event_func_ = (PF_CL_RELEASE_EVENT) getProcAddr( "clReleaseEvent");
//  }

//  if( release_event_func_ != NULL){
//    return release_event_func_(event);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_int OpenClLoader::clSetUserEventStatus(cl_event event, cl_int execution_status)
//{
//  if( set_user_event_status_func_ == NULL ){
//    set_user_event_status_func_ = (PF_CL_SET_USER_EVENT_STATUS) getProcAddr( "clSetUserEventStatus");
//  }

//  if( set_user_event_status_func_ != NULL){
//    return set_user_event_status_func_( event, execution_status);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_int OpenClLoader::clSetEventCallback(cl_event event, cl_int command_exec_callback_type, void (CL_CALLBACK *pfn_notify)(cl_event, cl_int, void *), void *user_data)
//{
//  if( set_event_callback_func_ == NULL ){
//    set_event_callback_func_ = (PF_CL_SET_EVENT_CALLBACK) getProcAddr( "clSetEventCallback");
//  }

//  if( set_event_callback_func_ != NULL){
//    return set_event_callback_func_( event, command_exec_callback_type, pfn_notify, user_data);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_int OpenClLoader::clFlush(cl_command_queue command_queue)
//{
//  if( flush_func_ == NULL ){
//    flush_func_ = (PF_CL_FLUSH) getProcAddr( "clFlush");
//  }

//  if( flush_func_ != NULL){
//    return flush_func_(command_queue);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_int OpenClLoader::clFinish(cl_command_queue command_queue)
//{
//  if( finish_func_ == NULL ){
//    finish_func_ = (PF_CL_FINISH) getProcAddr( "clFinish");
//  }

//  if( finish_func_ != NULL){
//    return finish_func_(command_queue);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_int OpenClLoader::clEnqueueReadBuffer(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, size_t offset, size_t cb, void *ptr, cl_uint num_events_in_wait, const cl_event *event_wait_list, cl_event *event)
//{
//  if( enqueue_read_buffer_func_ == NULL ){
//    enqueue_read_buffer_func_ = (PF_CL_ENQUEUE_READ_BUFFER) getProcAddr( "clEnqueueReadBuffer");
//  }

//  if( enqueue_read_buffer_func_ != NULL){
//    return enqueue_read_buffer_func_( command_queue, buffer, blocking_read, offset, cb, ptr, num_events_in_wait, event_wait_list, event);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_int OpenClLoader::clEnqueueReadBufferRect(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, const size_t * buffer_offset, const size_t *host_offset, const size_t *region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, void * ptr, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * event)
//{
//  if( enqueue_read_buffer_rect_func_ == NULL ){
//    enqueue_read_buffer_rect_func_ = (PF_CL_ENQUEUE_READ_BUFFER_RECT) getProcAddr( "clEnqueueReadBufferRect");
//  }

//  if( enqueue_read_buffer_rect_func_ != NULL){
//    return enqueue_read_buffer_rect_func_( command_queue, buffer, blocking_read, buffer_offset, host_offset, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_int OpenClLoader::clEnqueueWriteBuffer(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, size_t offset, size_t cb, const void *ptr, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event)
//{
//  if( enqueue_write_buffer_func_ == NULL ){
//    enqueue_write_buffer_func_ = (PF_CL_ENQUEUE_WRITE_BUFFER) getProcAddr( "clEnqueueWriteBuffer");
//  }

//  if( enqueue_write_buffer_func_ != NULL){
//    return enqueue_write_buffer_func_( command_queue, buffer, blocking_write, offset, cb, ptr, num_events_in_wait_list, event_wait_list, event );
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_int OpenClLoader::clEnqueueWriteBufferRect(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, const size_t *buffer_offset, const size_t *host_offset, const size_t *region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, const void *ptr, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event)
//{
//  if( enqueue_write_buffer_rect_func_ == NULL ){
//    enqueue_write_buffer_rect_func_ = (PF_CL_ENQUEUE_WRITE_BUFFER_RECT) getProcAddr( "clEnqueueWriteBufferRect");
//  }

//  if( enqueue_write_buffer_rect_func_ != NULL){
//    return enqueue_write_buffer_rect_func_( command_queue, buffer, blocking_read, buffer_offset, host_offset, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_int OpenClLoader::clEnqueueCopyBuffer(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_buffer, size_t src_offset, size_t dst_offset, size_t cb, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event)
//{
//  if( enqueue_copy_buffer_func_ == NULL ){
//    enqueue_copy_buffer_func_ = (PF_CL_ENQUEUE_COPY_BUFFER) getProcAddr( "clEnqueueCopyBuffer");
//  }

//  if( enqueue_copy_buffer_func_ != NULL){
//    return enqueue_copy_buffer_func_( command_queue, src_buffer, dst_buffer, src_offset, dst_offset, cb, num_events_in_wait_list, event_wait_list, event );
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_int OpenClLoader::clEnqueueCopyBufferRect(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_buffer, const size_t *src_origin, const size_t *dst_origin, const size_t *region, size_t src_row_pitch, size_t src_slice_pitch, size_t dst_row_pitch, size_t dst_slice_pitch, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event)
//{
//  if( enqueue_copy_buffer_rect_func_ == NULL ){
//    enqueue_copy_buffer_rect_func_ = (PF_CL_ENQUEUE_COPY_BUFFER_RECT) getProcAddr( "clEnqueueCopyBufferRect");
//  }

//  if( enqueue_copy_buffer_rect_func_ != NULL){
//    return enqueue_copy_buffer_rect_func_( command_queue, src_buffer, dst_buffer, src_origin, dst_origin, region, src_row_pitch, src_slice_pitch, dst_row_pitch, dst_slice_pitch, num_events_in_wait_list, event_wait_list, event);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_int OpenClLoader::clEnqueueReadImage(cl_command_queue command_queue, cl_mem image, cl_bool blocking_read, const size_t origin[], const size_t region[], size_t row_pitch, size_t slice_pitch, void *ptr, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event)
//{
//  if( enqueue_read_image_func_ == NULL ){
//    enqueue_read_image_func_ = (PF_CL_ENQUEUE_READ_IMAGE) getProcAddr( "clEnqueueReadImage");
//  }

//  if( enqueue_read_image_func_ != NULL){
//    return enqueue_read_image_func_( command_queue, image, blocking_read, origin, region, row_pitch, slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_int OpenClLoader::clEnqueueWriteImage(cl_command_queue command_queue, cl_mem image, cl_bool blocking_write, const size_t origin[], const size_t region[], size_t input_row_pitch, size_t input_slice_pitch, const void *ptr, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event)
//{
//  if( enqueue_write_image_func_ == NULL ){
//    enqueue_write_image_func_ = (PF_CL_ENQUEUE_WRITE_IMAGE) getProcAddr( "clEnqueueWriteImage");
//  }

//  if( enqueue_write_image_func_ != NULL){
//    return enqueue_write_image_func_( command_queue, image, blocking_write, origin, region, input_row_pitch, input_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event );
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_int OpenClLoader::clEnqueueCopyImage(cl_command_queue command_queue, cl_mem src_image, cl_mem dst_image, const size_t *src_origin, const size_t *dst_origin, const size_t *region, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event)
//{
//  if( enqueue_copy_image_func_ == NULL ){
//    enqueue_copy_image_func_ = (PF_CL_ENQUEUE_COPY_IMAGE) getProcAddr( "clEnqueueCopyImage");
//  }

//  if( enqueue_copy_image_func_ != NULL){
//    return enqueue_copy_image_func_( command_queue, src_image, dst_image, src_origin, dst_origin, region, num_events_in_wait_list, event_wait_list, event);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_int OpenClLoader::clEnqueueCopyImageToBuffer(cl_command_queue command_queue, cl_mem src_image, cl_mem dst_image, const size_t *src_origin, const size_t *region, size_t dst_offset, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event)
//{
//  if( enqueue_copy_image_to_buffer_func_ == NULL ){
//    enqueue_copy_image_to_buffer_func_ = (PF_CL_ENQUEUE_COPY_IMAGE_TO_BUFFER) getProcAddr( "clEnqueueCopyImageToBuffer");
//  }

//  if( enqueue_copy_image_to_buffer_func_ != NULL){
//    return enqueue_copy_image_to_buffer_func_( command_queue, src_image, dst_image, src_origin, region, dst_offset, num_events_in_wait_list, event_wait_list, event);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//void *OpenClLoader::clEnqueueMapBuffer(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_map, cl_map_flags map_flags, size_t offset, size_t cb, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event, cl_int *errcode_ret)
//{
//  if( enqueue_map_buffer_func_ == NULL ){
//    enqueue_map_buffer_func_ = (PF_CL_ENQUEUE_MAP_BUFFER) getProcAddr( "clEnqueueMapBuffer");
//  }

//  if( enqueue_map_buffer_func_ != NULL){
//    return enqueue_map_buffer_func_( command_queue,  buffer,  blocking_map,  map_flags, offset, cb, num_events_in_wait_list, event_wait_list, event, errcode_ret);
//  }else{
//    *errcode_ret = OPENCL_FUNCTION_BIND_FAIL;
//    return NULL;
//  }
//}

//void *OpenClLoader::clEnqueueMapImage(cl_command_queue command_queue, cl_mem image, cl_bool blocking_map, cl_map_flags map_flags, const size_t origin[], const size_t region[], size_t *image_row_pitch, size_t *image_slice_pitch, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event, cl_int *errcode_ret)
//{
//  if( enqueue_map_image_func_ == NULL ){
//    enqueue_map_image_func_ = (PF_CL_ENQUEUE_MAP_IMAGE) getProcAddr( "clEnqueueMapImage");
//  }

//  if( enqueue_map_image_func_ != NULL){
//    return enqueue_map_image_func_( command_queue,  image,  blocking_map,  map_flags,  origin,  region, image_row_pitch, image_slice_pitch, num_events_in_wait_list, event_wait_list, event, errcode_ret);
//  }else{
//    *errcode_ret = OPENCL_FUNCTION_BIND_FAIL;
//    return NULL;
//  }
//}

//cl_int OpenClLoader::clEnqueueUnmapMemObject(cl_command_queue command_queue, cl_mem memobj, void *mapped_ptr, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event)
//{
//  if( enqueue_unmap_mem_object_func_ == NULL ){
//    enqueue_unmap_mem_object_func_ = (PF_CL_ENQUEUE_UNMAP_MEM_OBJECT) getProcAddr( "clEnqueueUnmapMemObject");
//  }

//  if( enqueue_unmap_mem_object_func_ != NULL){
//    return enqueue_unmap_mem_object_func_( command_queue, memobj, mapped_ptr, num_events_in_wait_list, event_wait_list, event);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_int OpenClLoader::clEnqueueNDRangeKernel(cl_command_queue command_queue, cl_kernel kernel, cl_uint work_dim, const size_t *global_work_offset, const size_t *global_work_size, const size_t *local_work_size, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event)
//{
//  if( enqueue_nd_range_kernel_func_ == NULL ){
//    enqueue_nd_range_kernel_func_ = (PF_CL_ENQUEUE_ND_RANGE_KERNEL) getProcAddr( "clEnqueueNDRangeKernel");
//  }

//  if( enqueue_nd_range_kernel_func_ != NULL){
//    return enqueue_nd_range_kernel_func_( command_queue, kernel, work_dim, global_work_offset, global_work_size, local_work_size, num_events_in_wait_list, event_wait_list, event);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_int OpenClLoader::clEnqueueTask(cl_command_queue command_queue, cl_kernel kernel, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event)
//{
//  if( enqueue_task_func_ == NULL ){
//    enqueue_task_func_ = (PF_CL_ENQUEUE_TASK) getProcAddr( "clEnqueueTask");
//  }

//  if( enqueue_task_func_ != NULL){
//    return enqueue_task_func_( command_queue, kernel, num_events_in_wait_list, event_wait_list, event);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_int OpenClLoader::clEnqueueNativeKernel(cl_command_queue command_queue, void (*user_func)(void *), void *args, size_t cbargs, cl_uint num_mem_objects, const cl_mem *mem_list, const void **args_mem_loc, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event)
//{
//  if( enqueue_native_kernel_func_ == NULL ){
//    enqueue_native_kernel_func_ = (PF_CL_ENQUEUE_NATIVE_KERNEL) getProcAddr( "clEnqueueNativeKernel");
//  }

//  if( enqueue_native_kernel_func_ != NULL){
//    return enqueue_native_kernel_func_( command_queue, user_func, args, cbargs, num_mem_objects, mem_list, args_mem_loc,  num_events_in_wait_list, event_wait_list, event );
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_int OpenClLoader::clEnqueueMarker(cl_command_queue command_queue, cl_event *event)
//{
//  if( enqueue_marker_func_ == NULL ){
//    enqueue_marker_func_ = (PF_CL_ENQUEUE_MARKER) getProcAddr( "clEnqueueMarker");
//  }

//  if( enqueue_marker_func_ != NULL){
//    return enqueue_marker_func_(command_queue, event);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_int OpenClLoader::clEnqueueWaitForEvents(cl_command_queue command_queue, cl_uint num_events, const cl_event *event)
//{
//  if( enqueue_wait_for_events_func_ == NULL ){
//    enqueue_wait_for_events_func_ = (PF_CL_ENQUEUE_WAIT_FOR_EVENTS) getProcAddr( "clEnqueueWaitForEvents");
//  }

//  if( enqueue_wait_for_events_func_ != NULL){
//    return enqueue_wait_for_events_func_( command_queue,  num_events, event );
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_int OpenClLoader::clEnqueueBarrier(cl_command_queue command_queue)
//{
//  if( enqueue_barrier_func_ == NULL ){
//    enqueue_barrier_func_ = (PF_CL_ENQUEUE_BARRIER) getProcAddr( "clEnqueueBarrier");
//  }

//  if( enqueue_barrier_func_ != NULL){
//    return enqueue_barrier_func_(command_queue);
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_int OpenClLoader::clReleaseCommandQueue( cl_command_queue command_queue ) {
//  if( release_command_queue_func_ == NULL ){
//    release_command_queue_func_ = (PF_N_CL_RELEASE_COMMAND_QUEUE) getProcAddr( "clReleaseCommandQueue");
//  }

//  if( release_command_queue_func_ != NULL){
//    return release_command_queue_func_( command_queue );
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}

//cl_int OpenClLoader::clGetEventProfilingInfo( cl_event e, cl_profiling_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret )
//{
//  if( get_event_profiling_info_func_ == NULL ){
//    get_event_profiling_info_func_ = (PF_CL_GET_EVENT_PROFILING_INFO) getProcAddr( "clGetEventProfilingInfo");
//  }

//  if( get_event_profiling_info_func_ != NULL){
//    return get_event_profiling_info_func_( e, param_name, param_value_size, param_value, param_value_size_ret );
//  }else{
//    return OPENCL_FUNCTION_BIND_FAIL;
//  }
//}
