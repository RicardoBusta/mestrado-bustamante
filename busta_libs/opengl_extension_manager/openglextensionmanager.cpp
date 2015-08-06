#include "openglextensionmanager.h"

#if defined( _WIN32 )
#  define VOIDRETDECL(funcname,funcpointer,functype,...) \
  if( funcpointer == NULL ){ \
  funcpointer = ( functype )wglGetProcAddress( #funcname ); \
  } \
  if( funcpointer == NULL){ \
  return; \
  } \
  funcpointer ( __VA_ARGS__ );

#  define TYPERETDECL(funcname,funcpointer,functype,...) \
  if( funcpointer == NULL ){ \
  funcpointer = ( functype )wglGetProcAddress( #funcname ); \
  } \
  if( funcpointer == NULL){ \
  return GL_INVALID_ENUM; \
  } \
  return funcpointer ( __VA_ARGS__ );
#else // _WIN32
#  define VOIDRETDECL(funcname,funcpointer,functype,...) \
  funcname ( __VA_ARGS__ );
#  define TYPERETDECL(funcname,funcpointer,functype,...) \
  return funcname ( __VA_ARGS__ );
#endif

namespace Busta{

  OpenGL * OpenGL::instance_ = NULL;

  OpenGL *OpenGL::instance()
  {
    if(instance_ == NULL){
      instance_ = new OpenGL();
    }
    return instance_;
  }

  OpenGL::OpenGL()
  {
    gl_tex_image_3d_ = NULL;
    gl_gen_framebuffers_ = NULL;
    gl_bind_framebuffer_ = NULL;
    gl_check_framebuffer_status_ = NULL;
    gl_gen_renderbuffers_ = NULL;
    gl_renderbuffer_storage_ = NULL;
    gl_bind_renderbuffer_ = NULL;
    gl_framebuffer_renderbuffer_ = NULL;
    gl_framebuffer_texture_ = NULL;
    gl_draw_buffers_ = NULL;
  }

  void OpenGL::texImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels)
  {
    VOIDRETDECL(texImage3D,gl_tex_image_3d_,PFNGLTEXIMAGE3DPROC,target,level,internalformat,width,height,depth,border,format,type,pixels)
  }

  void OpenGL::glGenFramebuffers(GLsizei n, GLuint *ids)
  {
    VOIDRETDECL(glGenFramebuffers,gl_gen_framebuffers_,PFNGLGENFRAMEBUFFERSPROC,n,ids);
  }

  void OpenGL::glBindFramebuffer(GLenum target, GLuint framebuffer)
  {
    VOIDRETDECL(glBindFramebuffer,gl_bind_framebuffer_,PFNGLBINDFRAMEBUFFERPROC,target,framebuffer);
  }

  GLenum OpenGL::glCheckFramebufferStatus(GLenum target)
  {
    TYPERETDECL(glCheckFramebufferStatus,gl_check_framebuffer_status_,PFNGLCHECKFRAMEBUFFERSTATUSPROC,target);
  }

  void OpenGL::glGenRenderbuffers(GLsizei n, GLuint *renderbuffers)
  {
    VOIDRETDECL(glGenRenderbuffers,gl_gen_renderbuffers_,PFNGLGENRENDERBUFFERSPROC,n,renderbuffers);
  }

  void OpenGL::glBindRenderbuffer(GLenum target, GLuint renderbuffer)
  {
    VOIDRETDECL(glBindRenderbuffer,gl_bind_renderbuffer_,PFNGLBINDRENDERBUFFERPROC,target,renderbuffer);
  }

  void OpenGL::glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
  {
    VOIDRETDECL(glRenderbufferStorage,gl_renderbuffer_storage_,PFNGLRENDERBUFFERSTORAGEPROC,target,internalformat,width,height);
  }

  void OpenGL::glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
  {
    VOIDRETDECL(glFramebufferRenderbuffer,gl_framebuffer_renderbuffer_,PFNGLFRAMEBUFFERRENDERBUFFERPROC,target,attachment,renderbuffertarget,renderbuffer);
  }

  void OpenGL::glFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level)
  {
    VOIDRETDECL(glFramebufferTexture,gl_framebuffer_texture_,PFNGLFRAMEBUFFERTEXTUREPROC,target,attachment,texture,level);
  }

  void OpenGL::glDrawBuffers(GLsizei n, const GLenum *bufs)
  {
    VOIDRETDECL(glDrawBuffers,gl_draw_buffers_,PFNGLDRAWBUFFERSPROC,n,bufs);
  }

  void OpenGL::glDeleteBuffers(GLsizei n, const GLuint *buffers)
  {
    VOIDRETDECL(glDeleteBuffers,gl_delete_buffers_,PFNGLDELETEBUFFERSPROC,n,buffers);
  }

  void OpenGL::glGenBuffers(GLsizei n, GLuint *buffers)
  {
    VOIDRETDECL(glGenBuffers,gl_gen_buffers_,PFNGLGENBUFFERSPROC,n,buffers);
  }

  void OpenGL::glBindBuffer(GLenum target, GLuint buffer)
  {
    VOIDRETDECL(glBindBuffer,gl_bind_buffer_,PFNGLBINDBUFFERPROC,target,buffer);
  }

  void OpenGL::glBufferData(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage)
  {
    VOIDRETDECL(glBufferData,gl_buffer_data_,PFNGLBUFFERDATAPROC,target,size,data,usage);
  }

  void OpenGL::glDeleteProgram(GLuint program)
  {
    VOIDRETDECL(glDelteProgram,gl_delete_program_,PFNGLDELETEPROGRAMPROC,program);
  }

  void OpenGL::glBindVertexArray(GLuint array)
  {
    VOIDRETDECL(glBindVertexArray,gl_bind_vertex_array_,PFNGLBINDVERTEXARRAYPROC,array);
  }

  void OpenGL::glDeleteVertexArrays(GLsizei n, const GLuint *arrays)
  {
    VOIDRETDECL(glDeleteVertexArrays,gl_delete_vertex_arrays_,PFNGLDELETEVERTEXARRAYSPROC,n,arrays);
  }

  void OpenGL::glGenVertexArrays(GLsizei n, GLuint *arrays)
  {
    VOIDRETDECL(glGenVertexArrays,gl_gen_vertex_arrays_,PFNGLGENVERTEXARRAYSPROC,n,arrays);
  }

  void OpenGL::glBindAttribLocation(GLuint program, GLuint index, const GLchar *name)
  {
    VOIDRETDECL(glBindAttribLocation,gl_bind_attrib_location_,PFNGLBINDATTRIBLOCATIONPROC,program,index,name);
  }

  void OpenGL::glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data)
  {
    VOIDRETDECL(glBufferSubData,gl_buffer_sub_data_,PFNGLBUFFERSUBDATAPROC,target,offset,size,data);
  }

  void OpenGL::glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer)
  {
    VOIDRETDECL(glVertexAttribPointer,gl_vertex_attrib_pointer_,PFNGLVERTEXATTRIBPOINTERPROC,index,size,type,normalized,stride,pointer);
  }

  void OpenGL::glUseProgram(GLuint program)
  {
    VOIDRETDECL(glUseProgram,gl_use_program_,PFNGLUSEPROGRAMPROC,program);
  }

  void OpenGL::glEnableVertexAttribArray(GLuint index)
  {
    VOIDRETDECL(glEnableVertexAttribArray,gl_enable_vertex_attrib_array_,PFNGLENABLEVERTEXATTRIBARRAYPROC,index);
  }

  void OpenGL::glDisableVertexAttribArray(GLuint index)
  {
    VOIDRETDECL(glDisableVertexAttribArray,gl_disable_vertex_attrib_array_,PFNGLDISABLEVERTEXATTRIBARRAYPROC,index);
  }

  void OpenGL::glUniform1f(GLint location, GLfloat v0)
  {
    VOIDRETDECL(glUniform1f,gl_uniform_1f_,PFNGLUNIFORM1FPROC,location,v0);
  }

  void OpenGL::glUniform2f(GLint location, GLfloat v0, GLfloat v1)
  {
    VOIDRETDECL(glUniform2f,gl_uniform_2f_,PFNGLUNIFORM2FPROC,location,v0,v1);
  }

  void OpenGL::glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
  {
    VOIDRETDECL(glUniform3f,gl_uniform_3f_,PFNGLUNIFORM3FPROC,location,v0,v1,v2);
  }

  void OpenGL::glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
  {
    VOIDRETDECL(glUniform4f,gl_uniform_4f_,PFNGLUNIFORM4FPROC,location,v0,v1,v2,v3);
  }

  void OpenGL::glUniform1i(GLint location, GLint v0)
  {
    VOIDRETDECL(glUniform1i,gl_uniform_1i_,PFNGLUNIFORM1IPROC,location,v0);
  }

  void OpenGL::glUniform2i(GLint location, GLint v0, GLint v1)
  {
    VOIDRETDECL(glUniform2i,gl_uniform_2i_,PFNGLUNIFORM2IPROC,location,v0,v1);
  }

  void OpenGL::glUniform3i(GLint location, GLint v0, GLint v1, GLint v2)
  {
    VOIDRETDECL(glUniform3i,gl_uniform_3i_,PFNGLUNIFORM3IPROC,location,v0,v1,v2);
  }

  void OpenGL::glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
  {
    VOIDRETDECL(glUniform4i,gl_uniform_4i_,PFNGLUNIFORM4IPROC,location,v0,v1,v2,v3);
  }

  void OpenGL::glTexBuffer(GLenum target, GLenum internalformat, GLuint buffer)
  {
    VOIDRETDECL(glTexBuffer,gl_tex_buffer_,PFNGLTEXBUFFERPROC,target,internalformat,buffer);
  }

  void OpenGL::glUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
  {
    VOIDRETDECL(glUniformMatrix3x2fv,gl_uniform_matrix_3x2_fv_,PFNGLUNIFORMMATRIX3X2FVPROC,location,count,transpose,value);
  }

  void OpenGL::glUniform3fv(GLint location, GLsizei count, const GLfloat *value)
  {
    VOIDRETDECL(glUniform3fv,gl_uniform_3fv_,PFNGLUNIFORM3FVPROC,location,count,value);
  }

  GLint OpenGL::glGetUniformLocation(GLuint program, const GLchar *name)
  {
    TYPERETDECL(glGetUniformLocation,gl_get_uniform_location_,PFNGLGETUNIFORMLOCATIONPROC,program,name);
  }

  void OpenGL::glActiveTexture(GLenum texture)
  {
    VOIDRETDECL(glActiveTexture,gl_active_texture_,PFNGLACTIVETEXTUREPROC,texture);
  }

  GLint OpenGL::glGetAttribLocation(GLuint program, const GLchar *name)
  {
    TYPERETDECL(glGetAttribLocation,gl_get_attrib_location_,PFNGLGETATTRIBLOCATIONPROC,program,name);
  }

  void OpenGL::glUniform4fv(GLint location, GLsizei count, const GLfloat *value)
  {
    VOIDRETDECL(glUniform4fv,gl_uniform_4fv_,PFNGLUNIFORM4FVPROC,location,count,value);
  }

  void OpenGL::glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
  {
    VOIDRETDECL(glUniformMatrix4fv,gl_uniform_matrix_4fv_,PFNGLUNIFORMMATRIX4FVPROC,location,count,transpose,value);
  }

  void OpenGL::glDrawArraysInstancedARB(GLenum mode, GLint first, GLsizei count, GLsizei primcount)
  {
    VOIDRETDECL(glDrawArraysInstancedARB,gl_draw_arrays_instanced_arb_,PFNGLDRAWARRAYSINSTANCEDARBPROC,mode,first,count,primcount);
  }

  GLuint OpenGL::glCreateProgram()
  {
    TYPERETDECL(glCreateProgram,gl_create_program_,PFNGLCREATEPROGRAMPROC);
  }

  GLuint OpenGL::glCreateShader(GLenum shaderType)
  {
    TYPERETDECL(glCreateShader,gl_create_shader_,PFNGLCREATESHADERPROC,shaderType);
  }

  void OpenGL::glShaderSource(GLuint shader, GLsizei count, const GLchar **string, const GLint *length)
  {
    VOIDRETDECL(glShaderSource,gl_shader_source_,PFNGLSHADERSOURCEPROC,shader,count,string,length);
  }

  void OpenGL::glCompileShader(GLuint shader)
  {
    VOIDRETDECL(glCompileShader,gl_compile_shader_,PFNGLCOMPILESHADERPROC,shader);
  }

  void OpenGL::glGetShaderiv(GLuint shader, GLenum pname, GLint *params)
  {
    VOIDRETDECL(glGetShaderiv,gl_get_shader_iv_,PFNGLGETSHADERIVPROC,shader,pname,params);
  }

  void OpenGL::glGetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei *length, GLchar *infoLog)
  {
    VOIDRETDECL(glGetShaderInfoLog,gl_get_shader_info_log_,PFNGLGETSHADERINFOLOGPROC,shader,maxLength,length,infoLog);
  }

  void OpenGL::glAttachShader(GLuint program, GLuint shader)
  {
    VOIDRETDECL(glAttachShader,gl_attach_shader_,PFNGLATTACHSHADERPROC,program,shader);
  }

  void OpenGL::glDetachShader(GLuint program, GLuint shader)
  {
    VOIDRETDECL(glDetachShader,gl_detach_shader_,PFNGLDETACHSHADERPROC,program,shader);
  }

  void OpenGL::glDeleteShader(GLuint shader)
  {
    VOIDRETDECL(glDeleteShader,gl_delete_shader_,PFNGLDELETESHADERPROC,shader);
  }

  void OpenGL::glGetProgramiv(GLuint program, GLenum pname, GLint *params)
  {
    VOIDRETDECL(glGetProgramiv,gl_get_programiv_,PFNGLGETPROGRAMIVPROC,program,pname,params);
  }

  void OpenGL::glLinkProgram(GLuint program)
  {
    VOIDRETDECL(glLinkProgram,gl_link_program_,PFNGLLINKPROGRAMPROC,program);
  }

  void OpenGL::glGetProgramInfoLog(GLuint program, GLsizei maxLength, GLsizei *length, GLchar *infoLog)
  {
    VOIDRETDECL(glGetProgramInfoLog,gl_get_program_info_log_,PFNGLGETPROGRAMINFOLOGPROC,program,maxLength,length,infoLog);
  }

  void OpenGL::glDeleteRenderbuffers(GLsizei n, const GLuint *renderbuffers)
  {
    VOIDRETDECL(glDeleteRenderbuffers,gl_delete_renderbuffers_,PFNGLDELETERENDERBUFFERSPROC,n,renderbuffers);
  }

  void OpenGL::glDeleteFramebuffers(GLsizei n, GLuint *framebuffers)
  {
    VOIDRETDECL(glDeleteFramebuffers,gl_delete_framebuffers_,PFNGLDELETEFRAMEBUFFERSPROC,n,framebuffers);
  }

  void OpenGL::glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
  {
    VOIDRETDECL(glFramebufferTexture2D,gl_framebuffer_texture_2D_,PFNGLFRAMEBUFFERTEXTURE2DPROC,target,attachment,textarget,texture,level);
  }

  void OpenGL::glUniform2fv(GLint location, GLsizei count, const GLfloat *value)
  {
    VOIDRETDECL(glUniform2fv,gl_uniform_2fv_,PFNGLUNIFORM2FVPROC,location,count,value);
  }

}
