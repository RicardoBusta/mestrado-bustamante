#ifndef OPENCLMANAGER_H
#define OPENCLMANAGER_H

#include "busta_libs/opencl_manager/openclmanagerdefines.h"

#include "CL/cl.h"

#include <vector>

namespace Busta{

  class OpenCLManager
  {
  public:
    bool LoadLib();
    void UnloadLibrary();

    void SetupGPUDevice();
    cl_context GPUContext() const;
    std::vector<cl_device_id> GPUDevices() const;

    static OpenCLManager *instance();

    cl_int clGetPlatformIDs( cl_uint num_entries, cl_platform_id * platforms, cl_uint * num_platforms );
//    cl_int clGetPlatformInfo( cl_platform_id platform, cl_platform_info param_name, size_t param_value_size, void *param_value, size_t * param_value_size_ret );
    cl_int clGetDeviceIDs( cl_platform_id platform, cl_device_type device_type, cl_uint num_entries, cl_device_id * devices, cl_uint * num_devices );
//    cl_int clGetDeviceInfo( cl_device_id device, cl_device_info param_name, size_t param_value_size, void * param_value,size_t * param_value_size_ret );
    cl_context clCreateContext(const cl_context_properties * properties, cl_uint num_devices, const cl_device_id * devices, void ( CL_CALLBACK * pfn_notify)(const char *, const void *, size_t, void *), void * user_data, cl_int * errcode_ret);
//    cl_context clCreateContextFromType(const cl_context_properties * properties, cl_device_type device_type, void (CL_CALLBACK * pfn_notify)(const char *, const void *, size_t, void *), void * user_data, cl_int * errcode_ret);
//    cl_int clRetainContext( cl_context context );
//    cl_int clReleaseContext( cl_context context );
//    cl_int clGetContextInfo( cl_context context, cl_context_info param_name, size_t param_value_size, void * param_value, size_t *param_value_size_ret );
    cl_command_queue clCreateCommandQueue( cl_context context, cl_device_id device, cl_command_queue_properties properties, cl_int * errcode_ret );
//    cl_int clRetainCommandQueue( cl_command_queue command_queue );
//    cl_int clReleaseCommandQueue( cl_command_queue command_queue );
//    cl_int clGetCommandQueueInfo( cl_command_queue command_queue, cl_command_queue_info param_name, size_t param_value_size, void * param_value, size_t * param_value_size_ret);
//    cl_int clSetCommandQueueProperty( cl_command_queue command_queue, cl_command_queue_properties properties, cl_bool enable, cl_command_queue_properties * old_properties); //< if CL_USE_DEPRECATED_OPENCL_1_0_APIS (not thread safe)
    cl_mem clCreateBuffer( cl_context context, cl_mem_flags flags, size_t size, void * host_ptr, cl_int * errcode_ret );
//    cl_mem clCreateSubBuffer(cl_mem buffer, cl_mem_flags flags, cl_buffer_create_type buffer_create_type, const void * buffer_create_info, cl_int * errcode_ret);
//    cl_mem clCreateImage2D(cl_context context, cl_mem_flags flags, const cl_image_format * image_format, size_t image_width, size_t image_height, size_t image_row_pitch, void * host_ptr, cl_int * errcode_ret);
//    cl_mem clCreateImage3D(cl_context context, cl_mem_flags flags, const cl_image_format * image_format, size_t image_width, size_t image_height, size_t image_depth, size_t image_row_pitch, size_t image_slice_pitch, void * host_ptr, cl_int * errcode_ret);
//    cl_int clRetainMemObject(cl_mem memobj);
    cl_int clReleaseMemObject(cl_mem memobj);
//    cl_int clGetSupportedImageFormats(cl_context context, cl_mem_flags flags, cl_mem_object_type image_type, cl_uint num_entries, cl_image_format * image_formats, cl_uint * num_image_formats);
//    cl_int clGetMemObjectInfo(cl_mem memobj, cl_mem_info param_name, size_t param_value_size, void * param_value, size_t * param_value_size_ret);
//    cl_int clGetImageInfo(cl_mem image, cl_image_info param_name, size_t param_value_size, void * param_value, size_t * param_value_size_ret);
//    cl_int clSetMemObjectDestructorCallback(cl_mem memobj, void (CL_CALLBACK * pfn_notify)(cl_mem memobj, void * user_data), void * user_data);
//    cl_sampler clCreateSampler(cl_context context, cl_bool normalized_coords, cl_addressing_mode addressing_mode, cl_filter_mode filter_mode, cl_int * errcode_ret);
//    cl_int clRetainSampler(cl_sampler sampler);
//    cl_int clReleaseSampler(cl_sampler sampler);
//    cl_int clGetSamplerInfo(cl_sampler sampler, cl_sampler_info param_name, size_t param_value_size, void * param_value, size_t * param_value_size_ret);
    cl_program clCreateProgramWithSource(cl_context context, cl_uint count, const char ** strings, const size_t * lengths, cl_int * errcode_ret);
//    cl_program clCreateProgramWithBinary(cl_context context, cl_uint num_devices, const cl_device_id * device_list, const size_t * lengths, const unsigned char ** binaries, cl_int * binary_status, cl_int * errcode_ret);
//    cl_int clRetainProgram(cl_program program);
//    cl_int clReleaseProgram(cl_program program);
    cl_int clBuildProgram(cl_program program, cl_uint num_devices, const cl_device_id * device_list, const char * options, void (CL_CALLBACK * pfn_notify)(cl_program, void *), void * user_data);
//    cl_int clUnloadCompiler(void);
//    cl_int clGetProgramInfo(cl_program program, cl_program_info param_name, size_t param_value_size, void * param_value, size_t * param_value_size_ret);
    cl_int clGetProgramBuildInfo(cl_program program, cl_device_id device, cl_program_build_info param_name, size_t param_value_size, void * param_value, size_t * param_value_size_ret);
    cl_kernel clCreateKernel(cl_program program, const char * kernel_name, cl_int * errcode_ret);
//    cl_int clCreateKernelsInProgram(cl_program program, cl_uint num_kernels, cl_kernel * kernels, cl_uint * num_kernels_ret);
//    cl_int clRetainKernel(cl_kernel kernel);
//    cl_int clReleaseKernel(cl_kernel kernel);
    cl_int clSetKernelArg(cl_kernel kernel, cl_uint arg_index, size_t arg_size, const void * arg_value);
//    cl_int clGetKernelInfo(cl_kernel kernel, cl_kernel_info param_name, size_t param_value_size, void * param_value, size_t * param_value_size_ret);
//    cl_int clGetKernelWorkGroupInfo(cl_kernel kernel, cl_device_id device, cl_kernel_work_group_info param_name, size_t param_value_size, void * param_value, size_t * param_value_size_ret);
//    cl_int clWaitForEvents(cl_uint num_events, const cl_event * event_list);
//    cl_int clGetEventInfo(cl_event event, cl_event_info param_name, size_t param_value_size, void * param_value, size_t * param_value_size_ret);
//    cl_int clRetainEvent(cl_event event);
//    cl_int clReleaseEvent(cl_event event);
//    cl_int clSetUserEventStatus(cl_event event, cl_int execution_status);
//    cl_int clSetEventCallback(cl_event event, cl_int command_exec_callback_type, void (CL_CALLBACK * pfn_notify)(cl_event, cl_int, void *), void * user_data);
//    cl_int clGetEventProfilingInfo( cl_event e, cl_profiling_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret );
//    cl_int clFlush(cl_command_queue command_queue);
//    cl_int clFinish(cl_command_queue command_queue);
    cl_int clEnqueueReadBuffer(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, size_t offset, size_t cb, void * ptr, cl_uint num_events_in_wait, const cl_event * event_wait_list, cl_event * event);
//    cl_int clEnqueueReadBufferRect(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, const size_t * buffer_offset, const size_t *host_offset, const size_t *region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, void * ptr, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * event);
    cl_int clEnqueueWriteBuffer(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, size_t offset, size_t cb, const void * ptr, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * event);
//    cl_int clEnqueueWriteBufferRect(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, const size_t * buffer_offset, const size_t * host_offset, const size_t * region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, const void * ptr, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * event);
//    cl_int clEnqueueCopyBuffer(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_buffer, size_t src_offset, size_t dst_offset, size_t cb, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * event);
//    cl_int clEnqueueCopyBufferRect(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_buffer, const size_t * src_origin, const size_t * dst_origin, const size_t * region, size_t src_row_pitch, size_t src_slice_pitch, size_t dst_row_pitch, size_t dst_slice_pitch, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * event);
//    cl_int clEnqueueReadImage(cl_command_queue command_queue, cl_mem image, cl_bool blocking_read, const size_t origin[3], const size_t region[3], size_t row_pitch, size_t slice_pitch, void * ptr, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * event);
//    cl_int clEnqueueWriteImage(cl_command_queue command_queue, cl_mem image, cl_bool blocking_write, const size_t origin[3], const size_t region[3], size_t input_row_pitch, size_t input_slice_pitch, const void * ptr, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * event);
//    cl_int clEnqueueCopyImage(cl_command_queue command_queue, cl_mem src_image, cl_mem dst_image, const size_t src_origin[3], const size_t dst_origin[3], const size_t region[3], cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * event);
//    cl_int clEnqueueCopyImageToBuffer(cl_command_queue command_queue, cl_mem src_image, cl_mem dst_image, const size_t src_origin[3], const size_t region[3], size_t dst_offset, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * event);
//    void * clEnqueueMapBuffer(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_map, cl_map_flags map_flags, size_t offset, size_t cb, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * event, cl_int * errcode_ret);
//    void * clEnqueueMapImage(cl_command_queue command_queue, cl_mem image, cl_bool blocking_map, cl_map_flags map_flags, const size_t origin[3], const size_t region[3], size_t * image_row_pitch, size_t * image_slice_pitch, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * event, cl_int *errcode_ret);
//    cl_int clEnqueueUnmapMemObject(cl_command_queue command_queue, cl_mem memobj, void * mapped_ptr, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * event);
    cl_int clEnqueueNDRangeKernel(cl_command_queue command_queue, cl_kernel kernel, cl_uint work_dim, const size_t * global_work_offset, const size_t * global_work_size, const size_t * local_work_size, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * event);
//    cl_int clEnqueueTask(cl_command_queue command_queue, cl_kernel kernel, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * event);
//    cl_int clEnqueueNativeKernel(cl_command_queue command_queue, void (*user_func)(void *), void * args, size_t cb_args, cl_uint num_mem_objects, const cl_mem * mem_list, const void ** args_mem_loc, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event * event);
//    cl_int clEnqueueMarker(cl_command_queue command_queue, cl_event *event);
//    cl_int clEnqueueWaitForEvents(cl_command_queue command_queue, cl_uint num_events, const cl_event *event);
//    cl_int clEnqueueBarrier(cl_command_queue command_queue);
  private:
    OpenCLManager();
    ~OpenCLManager();

    PF_CL_GET_PLATFORM_IDS platform_id_func_;
    PF_CL_GET_PLATFORM_INFO platform_info_func_;
    PF_CL_GET_DEVICE_IDS get_device_ids_func_;
    PF_CL_GET_DEVICE_INFO get_device_info_func_;
    PF_CL_CREATE_CONTEXT create_context_func_;
    PF_CL_CREATE_CONTEXT_FROM_TYPE create_context_from_type_func_;
    PF_CL_RETAIN_CONTEXT retain_context_func_;
    PF_CL_RELEASE_CONTEXT release_context_func_;
    PF_CL_GET_CONTEXT_INFO get_context_info_func_;
    PF_CL_CREATE_COMMAND_QUEUE create_command_queue_func_;
    PF_CL_RETAIN_COMMAND_QUEUE retaing_command_queue_;
    PF_N_CL_RELEASE_COMMAND_QUEUE release_command_queue_func_;
    PF_CL_GET_COMMAND_QUEUE_INFO get_command_queue_info_func_;
    PF_CL_SET_COMMAND_QUEUE_PROPERTY set_command_queue_property_func_;
    PF_CL_CREATE_BUFFER create_buffer_func_;
    PF_CL_CREATE_SUBBUFFER create_subbuffer_func_;
    PF_CL_CREATE_IMAGE2D create_image_2d_func_;
    PF_CL_CREATE_IMAGE3D create_image_3d_func_;
    PF_CL_RETAIN_MEMOBJECT retain_mem_object_func_;
    PF_CL_RELEASE_MEMOBJECT release_mem_object_func_;
    PF_CL_GET_MEM_OBJECT_INFO get_mem_object_info_func_;
    PF_CL_GET_IMAGE_INFO get_image_info_func_;
    PF_CL_SET_MEM_OBJECT_DESTRUCTOR_CALLBACK set_mem_object_destructor_callback_func_;
    PF_CL_CREATE_SAMPLER create_sampler_func_;
    PF_CL_RETAIN_SAMPLER retain_sampler_func_;
    PF_CL_RELEASE_SAMPLER release_sampler_func_;
    PF_CL_GET_SAMPLER_INFO get_sampler_info_func_;
    PF_CL_CREATE_PROGRAM_WITH_SOURCE create_program_with_source_func_;
    PF_CL_CREATE_PROGRAM_WITH_BINARY create_program_with_binary_func_;
    PF_CL_RETAIN_PROGRAM retain_program_;
    PF_CL_RELEASE_PROGRAM release_program_func_;
    PF_CL_BUILD_PROGRAM build_program_func_;
    PF_CL_UNLOAD_COMPILER unload_compiler_func_;
    PF_CL_GET_PROGRAM_INFO get_program_info_func_;
    PF_CL_GET_PROGRAM_BUILD_INFO get_program_build_info_func_;
    PF_CL_CREATE_KERNEL create_kernel_func_;
    PF_CL_CREATE_KERNELS_IN_PROGRAM create_kernels_in_program_func_;
    PF_CL_RETAIN_KERNEL retain_kernel_func_;
    PF_CL_RELEASE_KERNEL release_kernel_func_;
    PF_CL_SET_KERNEL_ARG set_kerne_arg_func_;
    PF_CL_GET_KERNEL_INFO get_kernel_info_func_;
    PF_CL_GET_KERNEL_WORK_GROUP_INFO get_kernel_work_group_info_func_;
    PF_CL_WAIT_FOR_EVENTS wait_for_events_func_;
    PF_CL_GET_EVENT_INFO get_event_info_func_;
    PF_CL_RETAIN_EVENT retain_event_func_;
    PF_CL_RELEASE_EVENT release_event_func_;
    PF_CL_SET_USER_EVENT_STATUS set_user_event_status_func_;
    PF_CL_SET_EVENT_CALLBACK set_event_callback_func_;
    PF_CL_GET_EVENT_PROFILING_INFO get_event_profiling_info_func_;
    PF_CL_FLUSH flush_func_;
    PF_CL_FINISH finish_func_;
    PF_CL_ENQUEUE_READ_BUFFER enqueue_read_buffer_func_;
    PF_CL_ENQUEUE_READ_BUFFER_RECT enqueue_read_buffer_rect_func_;
    PF_CL_ENQUEUE_WRITE_BUFFER enqueue_write_buffer_func_;
    PF_CL_ENQUEUE_WRITE_BUFFER_RECT enqueue_write_buffer_rect_func_;
    PF_CL_ENQUEUE_COPY_BUFFER enqueue_copy_buffer_func_;
    PF_CL_ENQUEUE_COPY_BUFFER_RECT enqueue_copy_buffer_rect_func_;
    PF_CL_ENQUEUE_READ_IMAGE enqueue_read_image_func_;
    PF_CL_ENQUEUE_WRITE_IMAGE enqueue_write_image_func_;
    PF_CL_ENQUEUE_COPY_IMAGE enqueue_copy_image_func_;
    PF_CL_ENQUEUE_COPY_IMAGE_TO_BUFFER enqueue_copy_image_to_buffer_func_;
    PF_CL_ENQUEUE_COPY_BUFFER_TO_IMAGE enqueue_copy_buffer_to_image_func_;
    PF_CL_ENQUEUE_MAP_BUFFER enqueue_map_buffer_func_;
    PF_CL_ENQUEUE_MAP_IMAGE enqueue_map_image_func_;
    PF_CL_ENQUEUE_UNMAP_MEM_OBJECT enqueue_unmap_mem_object_func_;
    PF_CL_ENQUEUE_ND_RANGE_KERNEL enqueue_nd_range_kernel_func_;
    PF_CL_ENQUEUE_TASK enqueue_task_func_;
    PF_CL_ENQUEUE_NATIVE_KERNEL enqueue_native_kernel_func_;
    PF_CL_ENQUEUE_MARKER enqueue_marker_func_;
    PF_CL_ENQUEUE_WAIT_FOR_EVENTS enqueue_wait_for_events_func_;
    PF_CL_ENQUEUE_BARRIER enqueue_barrier_func_;

    void SetNull();
    void * const getProcAddr( const char * symbol );

    void * lib_;
    bool is_enabled_;

    bool bind_error_;

    std::vector<cl_device_id> gpu_devices_;
    cl_platform_id gpu_platform_;
    cl_context gpu_context_;
    bool gpu_setup_;

    static OpenCLManager * instance_;
  };

}

#endif // OPENCLMANAGER_H
