#ifndef OPENCLMANAGERDEFINES_H
#define OPENCLMANAGERDEFINES_H

#include <CL/cl.h>
#include <CL/cl_platform.h>

#if defined(_WIN32)
#define CL_API_ENTRY
#define CL_API_CALL     __stdcall
#define CL_CALLBACK     __stdcall
#else
#define CL_API_ENTRY
#define CL_API_CALL
#define CL_CALLBACK
#endif

namespace Busta{

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_GET_PLATFORM_IDS)(cl_uint          /* num_entries */,
                                                                     cl_platform_id * /* platforms */,
                                                                     cl_uint *        /* num_platforms */);

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_GET_PLATFORM_INFO)(cl_platform_id   /* platform */,
                                                                      cl_platform_info /* param_name */,
                                                                      size_t           /* param_value_size */,
                                                                      void *           /* param_value */,
                                                                      size_t *         /* param_value_size_ret */);

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_GET_DEVICE_IDS)(cl_platform_id   /* platform */,
                                                                   cl_device_type   /* device_type */,
                                                                   cl_uint          /* num_entries */,
                                                                   cl_device_id *   /* devices */,
                                                                   cl_uint *        /* num_devices */);

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_GET_DEVICE_INFO)(cl_device_id    /* device */,
                                                                    cl_device_info  /* param_name */,
                                                                    size_t          /* param_value_size */,
                                                                    void *          /* param_value */,
                                                                    size_t *        /* param_value_size_ret */);

  typedef CL_API_ENTRY cl_context (CL_API_CALL * PF_CL_CREATE_CONTEXT)(const cl_context_properties * /* properties */,
                                                                       cl_uint                       /* num_devices */,
                                                                       const cl_device_id *          /* devices */,
                                                                       void (CL_CALLBACK * pfn_notify)(const char *, const void *, size_t, void *) /* pfn_notify */,
                                                                       void *                        /* user_data */,
                                                                       cl_int *                      /* errcode_ret */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_context (CL_API_CALL * PF_CL_CREATE_CONTEXT_FROM_TYPE)(const cl_context_properties * /* properties */,
                                                                                 cl_device_type                /* device_type */,
                                                                                 void (CL_CALLBACK * pfn_notify)(const char *, const void *, size_t, void *) /* pfn_notify */,
                                                                                 void *                        /* user_data */,
                                                                                 cl_int *                      /* errcode_ret */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_RETAIN_CONTEXT)(cl_context /* context */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL *PF_CL_RELEASE_CONTEXT)(cl_context /* context */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_GET_CONTEXT_INFO)(cl_context         /* context */,
                                                                     cl_context_info    /* param_name */,
                                                                     size_t             /* param_value_size */,
                                                                     void *             /* param_value */,
                                                                     size_t *           /* param_value_size_ret */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_command_queue (CL_API_CALL * PF_CL_CREATE_COMMAND_QUEUE)(cl_context                     /* context */,
                                                                                   cl_device_id                   /* device */,
                                                                                   cl_command_queue_properties    /* properties */,
                                                                                   cl_int *                       /* errcode_ret */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_RETAIN_COMMAND_QUEUE)(cl_command_queue /* command_queue */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_N_CL_RELEASE_COMMAND_QUEUE)(cl_command_queue /* command_queue */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_GET_COMMAND_QUEUE_INFO)(cl_command_queue      /* command_queue */,
                                                                           cl_command_queue_info /* param_name */,
                                                                           size_t                /* param_value_size */,
                                                                           void *                /* param_value */,
                                                                           size_t *              /* param_value_size_ret */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_SET_COMMAND_QUEUE_PROPERTY)(cl_command_queue              /* command_queue */,
                                                                               cl_command_queue_properties   /* properties */,
                                                                               cl_bool                        /* enable */,
                                                                               cl_command_queue_properties * /* old_properties */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_mem (CL_API_CALL * PF_CL_CREATE_BUFFER)(cl_context   /* context */,
                                                                  cl_mem_flags /* flags */,
                                                                  size_t       /* size */,
                                                                  void *       /* host_ptr */,
                                                                  cl_int *     /* errcode_ret */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_mem (CL_API_CALL * PF_CL_CREATE_SUBBUFFER)(cl_mem   			/* buffer */,
                                                                     cl_mem_flags 			/* flags */,
                                                                     cl_buffer_create_type    /* buffer_create_type */,
                                                                     const void *       		/* buffer_create_info */,
                                                                     cl_int *     			/* errcode_ret */) CL_API_SUFFIX__VERSION_1_1;

  typedef CL_API_ENTRY cl_mem (CL_API_CALL * PF_CL_CREATE_IMAGE2D)(cl_context              /* context */,
                                                                   cl_mem_flags            /* flags */,
                                                                   const cl_image_format * /* image_format */,
                                                                   size_t                  /* image_width */,
                                                                   size_t                  /* image_height */,
                                                                   size_t                  /* image_row_pitch */,
                                                                   void *                  /* host_ptr */,
                                                                   cl_int *                /* errcode_ret */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_mem (CL_API_CALL * PF_CL_CREATE_IMAGE3D)(cl_context              /* context */,
                                                                   cl_mem_flags            /* flags */,
                                                                   const cl_image_format * /* image_format */,
                                                                   size_t                  /* image_width */,
                                                                   size_t                  /* image_height */,
                                                                   size_t                  /* image_depth */,
                                                                   size_t                  /* image_row_pitch */,
                                                                   size_t                  /* image_slice_pitch */,
                                                                   void *                  /* host_ptr */,
                                                                   cl_int *                /* errcode_ret */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_RETAIN_MEMOBJECT)(cl_mem /* memobj */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_RELEASE_MEMOBJECT)(cl_mem /* memobj */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_GET_SUPPORTED_IMAGE_FORMATS)(cl_context           /* context */,
                                                                                cl_mem_flags         /* flags */,
                                                                                cl_mem_object_type   /* image_type */,
                                                                                cl_uint              /* num_entries */,
                                                                                cl_image_format *    /* image_formats */,
                                                                                cl_uint *            /* num_image_formats */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_GET_MEM_OBJECT_INFO)(cl_mem           /* memobj */,
                                                                        cl_mem_info      /* param_name */,
                                                                        size_t           /* param_value_size */,
                                                                        void *           /* param_value */,
                                                                        size_t *         /* param_value_size_ret */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_GET_IMAGE_INFO)(cl_mem           /* image */,
                                                                   cl_image_info    /* param_name */,
                                                                   size_t           /* param_value_size */,
                                                                   void *           /* param_value */,
                                                                   size_t *         /* param_value_size_ret */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_SET_MEM_OBJECT_DESTRUCTOR_CALLBACK)( cl_mem /* memobj */,
                                                                                        void (CL_CALLBACK * /*pfn_notify*/)( cl_mem /* memobj */, void* /*user_data*/),
                                                                                        void * /*user_data */ )             CL_API_SUFFIX__VERSION_1_1;

  /* Sampler APIs  */
  typedef CL_API_ENTRY cl_sampler (CL_API_CALL * PF_CL_CREATE_SAMPLER)(cl_context          /* context */,
                                                                       cl_bool             /* normalized_coords */,
                                                                       cl_addressing_mode  /* addressing_mode */,
                                                                       cl_filter_mode      /* filter_mode */,
                                                                       cl_int *            /* errcode_ret */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_RETAIN_SAMPLER)(cl_sampler /* sampler */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_RELEASE_SAMPLER)(cl_sampler /* sampler */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_GET_SAMPLER_INFO)(cl_sampler         /* sampler */,
                                                                     cl_sampler_info    /* param_name */,
                                                                     size_t             /* param_value_size */,
                                                                     void *             /* param_value */,
                                                                     size_t *           /* param_value_size_ret */) CL_API_SUFFIX__VERSION_1_0;

  /* Program Object APIs  */
  typedef CL_API_ENTRY cl_program (CL_API_CALL * PF_CL_CREATE_PROGRAM_WITH_SOURCE)(cl_context        /* context */,
                                                                                   cl_uint           /* count */,
                                                                                   const char **     /* strings */,
                                                                                   const size_t *    /* lengths */,
                                                                                   cl_int *          /* errcode_ret */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_program (CL_API_CALL * PF_CL_CREATE_PROGRAM_WITH_BINARY)(cl_context                     /* context */,
                                                                                   cl_uint                        /* num_devices */,
                                                                                   const cl_device_id *           /* device_list */,
                                                                                   const size_t *                 /* lengths */,
                                                                                   const unsigned char **         /* binaries */,
                                                                                   cl_int *                       /* binary_status */,
                                                                                   cl_int *                       /* errcode_ret */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_RETAIN_PROGRAM)(cl_program /* program */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_RELEASE_PROGRAM)(cl_program /* program */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_BUILD_PROGRAM)(cl_program           /* program */,
                                                                  cl_uint              /* num_devices */,
                                                                  const cl_device_id * /* device_list */,
                                                                  const char *         /* options */,
                                                                  void (CL_CALLBACK *  /* pfn_notify */)(cl_program /* program */, void * /* user_data */),
                                                                  void *               /* user_data */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_UNLOAD_COMPILER)(void) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_GET_PROGRAM_INFO)(cl_program         /* program */,
                                                                     cl_program_info    /* param_name */,
                                                                     size_t             /* param_value_size */,
                                                                     void *             /* param_value */,
                                                                     size_t *           /* param_value_size_ret */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_GET_PROGRAM_BUILD_INFO)(cl_program            /* program */,
                                                                           cl_device_id          /* device */,
                                                                           cl_program_build_info /* param_name */,
                                                                           size_t                /* param_value_size */,
                                                                           void *                /* param_value */,
                                                                           size_t *              /* param_value_size_ret */) CL_API_SUFFIX__VERSION_1_0;

  /* Kernel Object APIs */
  typedef CL_API_ENTRY cl_kernel (CL_API_CALL * PF_CL_CREATE_KERNEL)(cl_program      /* program */,
                                                                     const char *    /* kernel_name */,
                                                                     cl_int *        /* errcode_ret */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_CREATE_KERNELS_IN_PROGRAM)(cl_program     /* program */,
                                                                              cl_uint        /* num_kernels */,
                                                                              cl_kernel *    /* kernels */,
                                                                              cl_uint *      /* num_kernels_ret */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_RETAIN_KERNEL)(cl_kernel    /* kernel */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_RELEASE_KERNEL)(cl_kernel   /* kernel */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_SET_KERNEL_ARG)(cl_kernel    /* kernel */,
                                                                   cl_uint      /* arg_index */,
                                                                   size_t       /* arg_size */,
                                                                   const void * /* arg_value */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_GET_KERNEL_INFO)(cl_kernel       /* kernel */,
                                                                    cl_kernel_info  /* param_name */,
                                                                    size_t          /* param_value_size */,
                                                                    void *          /* param_value */,
                                                                    size_t *        /* param_value_size_ret */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_GET_KERNEL_WORK_GROUP_INFO)(cl_kernel                  /* kernel */,
                                                                               cl_device_id               /* device */,
                                                                               cl_kernel_work_group_info  /* param_name */,
                                                                               size_t                     /* param_value_size */,
                                                                               void *                     /* param_value */,
                                                                               size_t *                   /* param_value_size_ret */) CL_API_SUFFIX__VERSION_1_0;

  // Event Object APIs
  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_WAIT_FOR_EVENTS)(cl_uint             /* num_events */,
                                                                    const cl_event *    /* event_list */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_GET_EVENT_INFO)(cl_event         /* event */,
                                                                   cl_event_info    /* param_name */,
                                                                   size_t           /* param_value_size */,
                                                                   void *           /* param_value */,
                                                                   size_t *         /* param_value_size_ret */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_event (CL_API_CALL * PF_CL_CREATE_USER_EVENT)(cl_context    /* context */,
                                                                        cl_int *      /* errcode_ret */) CL_API_SUFFIX__VERSION_1_1;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_RETAIN_EVENT)(cl_event /* event */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_RELEASE_EVENT)(cl_event /* event */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_SET_USER_EVENT_STATUS)(cl_event   /* event */,
                                                                          cl_int     /* execution_status */) CL_API_SUFFIX__VERSION_1_1;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_SET_EVENT_CALLBACK)(cl_event    /* event */,
                                                                       cl_int      /* command_exec_callback_type */,
                                                                       void (CL_CALLBACK * /* pfn_notify */)(cl_event, cl_int, void *),
                                                                       void *      /* user_data */) CL_API_SUFFIX__VERSION_1_1;

  /* Profiling APIs  */
  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_GET_EVENT_PROFILING_INFO)(cl_event            /* event */,
                                                                             cl_profiling_info   /* param_name */,
                                                                             size_t              /* param_value_size */,
                                                                             void *              /* param_value */,
                                                                             size_t *            /* param_value_size_ret */) CL_API_SUFFIX__VERSION_1_0;

  /* Flush and Finish APIs */
  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_FLUSH)(cl_command_queue /* command_queue */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_FINISH)(cl_command_queue /* command_queue */) CL_API_SUFFIX__VERSION_1_0;

  /* Enqueued Commands APIs */
  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_ENQUEUE_READ_BUFFER)(cl_command_queue    /* command_queue */,
                                                                        cl_mem              /* buffer */,
                                                                        cl_bool             /* blocking_read */,
                                                                        size_t              /* offset */,
                                                                        size_t              /* cb */,
                                                                        void *              /* ptr */,
                                                                        cl_uint             /* num_events_in_wait_list */,
                                                                        const cl_event *    /* event_wait_list */,
                                                                        cl_event *          /* event */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_ENQUEUE_READ_BUFFER_RECT)(cl_command_queue    /* command_queue */,
                                                                             cl_mem              /* buffer */,
                                                                             cl_bool             /* blocking_read */,
                                                                             const size_t *      /* buffer_origin */,
                                                                             const size_t *      /* host_origin */,
                                                                             const size_t *      /* region */,
                                                                             size_t              /* buffer_row_pitch */,
                                                                             size_t              /* buffer_slice_pitch */,
                                                                             size_t              /* host_row_pitch */,
                                                                             size_t              /* host_slice_pitch */,
                                                                             void *              /* ptr */,
                                                                             cl_uint             /* num_events_in_wait_list */,
                                                                             const cl_event *    /* event_wait_list */,
                                                                             cl_event *          /* event */) CL_API_SUFFIX__VERSION_1_1;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_ENQUEUE_WRITE_BUFFER)(cl_command_queue   /* command_queue */,
                                                                         cl_mem             /* buffer */,
                                                                         cl_bool            /* blocking_write */,
                                                                         size_t             /* offset */,
                                                                         size_t             /* cb */,
                                                                         const void *       /* ptr */,
                                                                         cl_uint            /* num_events_in_wait_list */,
                                                                         const cl_event *   /* event_wait_list */,
                                                                         cl_event *         /* event */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_ENQUEUE_WRITE_BUFFER_RECT)(cl_command_queue    /* command_queue */,
                                                                              cl_mem              /* buffer */,
                                                                              cl_bool             /* blocking_write */,
                                                                              const size_t *      /* buffer_origin */,
                                                                              const size_t *      /* host_origin */,
                                                                              const size_t *      /* region */,
                                                                              size_t              /* buffer_row_pitch */,
                                                                              size_t              /* buffer_slice_pitch */,
                                                                              size_t              /* host_row_pitch */,
                                                                              size_t              /* host_slice_pitch */,
                                                                              const void *        /* ptr */,
                                                                              cl_uint             /* num_events_in_wait_list */,
                                                                              const cl_event *    /* event_wait_list */,
                                                                              cl_event *          /* event */) CL_API_SUFFIX__VERSION_1_1;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_ENQUEUE_COPY_BUFFER)(cl_command_queue    /* command_queue */,
                                                                        cl_mem              /* src_buffer */,
                                                                        cl_mem              /* dst_buffer */,
                                                                        size_t              /* src_offset */,
                                                                        size_t              /* dst_offset */,
                                                                        size_t              /* cb */,
                                                                        cl_uint             /* num_events_in_wait_list */,
                                                                        const cl_event *    /* event_wait_list */,
                                                                        cl_event *          /* event */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_ENQUEUE_COPY_BUFFER_RECT)(cl_command_queue    /* command_queue */,
                                                                             cl_mem              /* src_buffer */,
                                                                             cl_mem              /* dst_buffer */,
                                                                             const size_t *      /* src_origin */,
                                                                             const size_t *      /* dst_origin */,
                                                                             const size_t *      /* region */,
                                                                             size_t              /* src_row_pitch */,
                                                                             size_t              /* src_slice_pitch */,
                                                                             size_t              /* dst_row_pitch */,
                                                                             size_t              /* dst_slice_pitch */,
                                                                             cl_uint             /* num_events_in_wait_list */,
                                                                             const cl_event *    /* event_wait_list */,
                                                                             cl_event *          /* event */) CL_API_SUFFIX__VERSION_1_1;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_ENQUEUE_READ_IMAGE)(cl_command_queue     /* command_queue */,
                                                                       cl_mem               /* image */,
                                                                       cl_bool              /* blocking_read */,
                                                                       const size_t *       /* origin[3] */,
                                                                       const size_t *       /* region[3] */,
                                                                       size_t               /* row_pitch */,
                                                                       size_t               /* slice_pitch */,
                                                                       void *               /* ptr */,
                                                                       cl_uint              /* num_events_in_wait_list */,
                                                                       const cl_event *     /* event_wait_list */,
                                                                       cl_event *           /* event */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_ENQUEUE_WRITE_IMAGE)(cl_command_queue    /* command_queue */,
                                                                        cl_mem              /* image */,
                                                                        cl_bool             /* blocking_write */,
                                                                        const size_t *      /* origin[3] */,
                                                                        const size_t *      /* region[3] */,
                                                                        size_t              /* input_row_pitch */,
                                                                        size_t              /* input_slice_pitch */,
                                                                        const void *        /* ptr */,
                                                                        cl_uint             /* num_events_in_wait_list */,
                                                                        const cl_event *    /* event_wait_list */,
                                                                        cl_event *          /* event */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_ENQUEUE_COPY_IMAGE)(cl_command_queue     /* command_queue */,
                                                                       cl_mem               /* src_image */,
                                                                       cl_mem               /* dst_image */,
                                                                       const size_t *       /* src_origin[3] */,
                                                                       const size_t *       /* dst_origin[3] */,
                                                                       const size_t *       /* region[3] */,
                                                                       cl_uint              /* num_events_in_wait_list */,
                                                                       const cl_event *     /* event_wait_list */,
                                                                       cl_event *           /* event */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_ENQUEUE_COPY_IMAGE_TO_BUFFER)(cl_command_queue /* command_queue */,
                                                                                 cl_mem           /* src_image */,
                                                                                 cl_mem           /* dst_buffer */,
                                                                                 const size_t *   /* src_origin[3] */,
                                                                                 const size_t *   /* region[3] */,
                                                                                 size_t           /* dst_offset */,
                                                                                 cl_uint          /* num_events_in_wait_list */,
                                                                                 const cl_event * /* event_wait_list */,
                                                                                 cl_event *       /* event */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_ENQUEUE_COPY_BUFFER_TO_IMAGE)(cl_command_queue /* command_queue */,
                                                                                 cl_mem           /* src_buffer */,
                                                                                 cl_mem           /* dst_image */,
                                                                                 size_t           /* src_offset */,
                                                                                 const size_t *   /* dst_origin[3] */,
                                                                                 const size_t *   /* region[3] */,
                                                                                 cl_uint          /* num_events_in_wait_list */,
                                                                                 const cl_event * /* event_wait_list */,
                                                                                 cl_event *       /* event */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY void * (CL_API_CALL * PF_CL_ENQUEUE_MAP_BUFFER)(cl_command_queue /* command_queue */,
                                                                       cl_mem           /* buffer */,
                                                                       cl_bool          /* blocking_map */,
                                                                       cl_map_flags     /* map_flags */,
                                                                       size_t           /* offset */,
                                                                       size_t           /* cb */,
                                                                       cl_uint          /* num_events_in_wait_list */,
                                                                       const cl_event * /* event_wait_list */,
                                                                       cl_event *       /* event */,
                                                                       cl_int *         /* errcode_ret */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY void * (CL_API_CALL * PF_CL_ENQUEUE_MAP_IMAGE)(cl_command_queue  /* command_queue */,
                                                                      cl_mem            /* image */,
                                                                      cl_bool           /* blocking_map */,
                                                                      cl_map_flags      /* map_flags */,
                                                                      const size_t *    /* origin[3] */,
                                                                      const size_t *    /* region[3] */,
                                                                      size_t *          /* image_row_pitch */,
                                                                      size_t *          /* image_slice_pitch */,
                                                                      cl_uint           /* num_events_in_wait_list */,
                                                                      const cl_event *  /* event_wait_list */,
                                                                      cl_event *        /* event */,
                                                                      cl_int *          /* errcode_ret */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_ENQUEUE_UNMAP_MEM_OBJECT)(cl_command_queue /* command_queue */,
                                                                             cl_mem           /* memobj */,
                                                                             void *           /* mapped_ptr */,
                                                                             cl_uint          /* num_events_in_wait_list */,
                                                                             const cl_event *  /* event_wait_list */,
                                                                             cl_event *        /* event */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_ENQUEUE_ND_RANGE_KERNEL)(cl_command_queue /* command_queue */,
                                                                            cl_kernel        /* kernel */,
                                                                            cl_uint          /* work_dim */,
                                                                            const size_t *   /* global_work_offset */,
                                                                            const size_t *   /* global_work_size */,
                                                                            const size_t *   /* local_work_size */,
                                                                            cl_uint          /* num_events_in_wait_list */,
                                                                            const cl_event * /* event_wait_list */,
                                                                            cl_event *       /* event */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_ENQUEUE_TASK)(cl_command_queue  /* command_queue */,
                                                                 cl_kernel         /* kernel */,
                                                                 cl_uint           /* num_events_in_wait_list */,
                                                                 const cl_event *  /* event_wait_list */,
                                                                 cl_event *        /* event */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_ENQUEUE_NATIVE_KERNEL)(cl_command_queue  /* command_queue */,
                                                                          void (*user_func)(void *),
                                                                          void *            /* args */,
                                                                          size_t            /* cb_args */,
                                                                          cl_uint           /* num_mem_objects */,
                                                                          const cl_mem *    /* mem_list */,
                                                                          const void **     /* args_mem_loc */,
                                                                          cl_uint           /* num_events_in_wait_list */,
                                                                          const cl_event *  /* event_wait_list */,
                                                                          cl_event *        /* event */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_ENQUEUE_MARKER)(cl_command_queue    /* command_queue */,
                                                                   cl_event *          /* event */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_ENQUEUE_WAIT_FOR_EVENTS)(cl_command_queue /* command_queue */,
                                                                            cl_uint          /* num_events */,
                                                                            const cl_event * /* event_list */) CL_API_SUFFIX__VERSION_1_0;

  typedef CL_API_ENTRY cl_int (CL_API_CALL * PF_CL_ENQUEUE_BARRIER)(cl_command_queue /* command_queue */) CL_API_SUFFIX__VERSION_1_0;

}
#endif // OPENCLMANAGERDEFINES_H
