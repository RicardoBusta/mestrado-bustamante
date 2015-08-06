#ifndef BUSTA_OPENGLEXTENSIONMANAGER_H
#define BUSTA_OPENGLEXTENSIONMANAGER_H

#include "GL/gl.h"
#include "glext.h"

namespace Busta{

class OpenGL
{
public:
  static OpenGL * instance();

  void texImage3D(
      GLenum target,
      GLint level,
      GLint internalFormat,
      GLsizei width,
      GLsizei height,
      GLsizei depth,
      GLint border,
      GLenum format,
      GLenum type,
      const GLvoid * data
      );

  void glGenFramebuffers(
      GLsizei n,
      GLuint *ids
      );

  void glBindFramebuffer(
      GLenum target,
      GLuint framebuffer
      );

  GLenum glCheckFramebufferStatus(
      GLenum target
      );

  void glGenRenderbuffers(
      GLsizei n,
      GLuint *renderbuffers
      );

  void glBindRenderbuffer(
      GLenum target,
      GLuint renderbuffer
      );

  void glRenderbufferStorage(
      GLenum target,
      GLenum internalformat,
      GLsizei width,
      GLsizei height
      );

  void glFramebufferRenderbuffer(
      GLenum target,
      GLenum attachment,
      GLenum renderbuffertarget,
      GLuint renderbuffer
      );

  void glFramebufferTexture(
      GLenum target,
      GLenum attachment,
      GLuint texture,
      GLint level
      );

  void glDrawBuffers(
      GLsizei n,
      const GLenum *bufs
      );

  void glDeleteBuffers(
      GLsizei n,
      const GLuint * buffers
      );

  void glGenBuffers(
      GLsizei n,
      GLuint * buffers
      );

  void glBindBuffer(
      GLenum target,
      GLuint buffer
      );

  void glBufferData(
      GLenum  	target,
      GLsizeiptr  	size,
      const GLvoid *  	data,
      GLenum  	usage
      );

  void glDeleteProgram(
      GLuint program
      );

  void glBindVertexArray(
      GLuint array
      );

  void glDeleteVertexArrays(
      GLsizei n,
      const GLuint *arrays
      );

  void glGenVertexArrays(
      GLsizei n,
      GLuint *arrays
      );

  void glBindAttribLocation(
      GLuint program,
      GLuint index,
      const GLchar *name);

  void glBufferSubData(
      GLenum  	target,
      GLintptr  	offset,
      GLsizeiptr  	size,
      const GLvoid *  	data
      );

  void glVertexAttribPointer(
      GLuint  	index,
      GLint  	size,
      GLenum  	type,
      GLboolean  	normalized,
      GLsizei  	stride,
      const GLvoid *  	pointer
      );

  void glUseProgram(
      GLuint program
      );

  void glEnableVertexAttribArray(
      GLuint index
      );

  void glDisableVertexAttribArray(
      GLuint index
      );

  void glUniform1f(
      GLint location,
      GLfloat v0
      );

  void glUniform2f(
      GLint location,
      GLfloat v0,
      GLfloat v1
      );

  void glUniform3f(
      GLint location,
      GLfloat v0,
      GLfloat v1,
      GLfloat v2
      );

  void glUniform4f(
      GLint location,
      GLfloat v0,
      GLfloat v1,
      GLfloat v2,
      GLfloat v3
      );

  void glUniform1i(
      GLint location,
      GLint v0
      );

  void glUniform2i(
      GLint location,
      GLint v0,
      GLint v1
      );

  void glUniform3i(
      GLint location,
      GLint v0,
      GLint v1,
      GLint v2
      );

  void glUniform4i(
      GLint location,
      GLint v0,
      GLint v1,
      GLint v2,
      GLint v3
      );

  void glTexBuffer(
      GLenum target,
      GLenum internalFormat,
      GLuint buffer
      );

  void glUniformMatrix3x2fv(
      GLint location,
      GLsizei count,
      GLboolean transpose,
      const GLfloat *value
      );

  void glUniform3fv(
      GLint location,
      GLsizei count,
      const GLfloat *value
      );

  GLint glGetUniformLocation(
      GLuint program,
      const GLchar *name
      );

  void glActiveTexture(
      GLenum texture
      );

  GLint glGetAttribLocation(
      GLuint  	program,
      const GLchar * 	name
      );


  void glUniform4fv(
      GLint location,
      GLsizei count,
      const GLfloat *value
      );

  void glUniformMatrix4fv(
      GLint location,
      GLsizei count,
      GLboolean transpose,
      const GLfloat *value
      );

  void glDrawArraysInstancedARB (
      GLenum mode,
      GLint first,
      GLsizei count,
      GLsizei primcount
      );

  GLuint glCreateProgram(
      void
      );

  GLuint glCreateShader(
      GLenum shaderType
      );

  void glShaderSource(
      GLuint shader,
      GLsizei count,
      const GLchar **string,
      const GLint *length
      );

  void glCompileShader(
      GLuint shader
      );

  void glGetShaderiv(
      GLuint shader,
      GLenum pname,
      GLint *params
      );

  void glGetShaderInfoLog(
      GLuint shader,
      GLsizei maxLength,
      GLsizei *length,
      GLchar *infoLog
      );

  void glAttachShader(
      GLuint program,
      GLuint shader
      );

  void glDetachShader(
      GLuint program,
      GLuint shader
      );

  void glDeleteShader(
      GLuint shader
      );

  void glGetProgramiv(
      GLuint program,
      GLenum pname,
      GLint *params
      );

  void glLinkProgram(
      GLuint program
      );

  void glGetProgramInfoLog(
      GLuint program,
      GLsizei maxLength,
      GLsizei *length,
      GLchar *infoLog
      );

  void glDeleteRenderbuffers(
      GLsizei n,
    const GLuint * renderbuffers
      );

  void glDeleteFramebuffers(
      GLsizei n,
    GLuint *framebuffers
      );

  void glFramebufferTexture2D(	GLenum target,
    GLenum attachment,
    GLenum textarget,
    GLuint texture,
    GLint level);

  void glUniform2fv(	GLint location,
    GLsizei count,
    const GLfloat *value);

private:
  OpenGL();

  static OpenGL * instance_;

  PFNGLTEXIMAGE3DPROC gl_tex_image_3d_;
  PFNGLGENFRAMEBUFFERSPROC gl_gen_framebuffers_;
  PFNGLBINDFRAMEBUFFERPROC gl_bind_framebuffer_;
  PFNGLCHECKFRAMEBUFFERSTATUSPROC gl_check_framebuffer_status_;
  PFNGLGENRENDERBUFFERSPROC gl_gen_renderbuffers_;
  PFNGLRENDERBUFFERSTORAGEPROC gl_renderbuffer_storage_;
  PFNGLBINDRENDERBUFFERPROC gl_bind_renderbuffer_;
  PFNGLFRAMEBUFFERRENDERBUFFERPROC gl_framebuffer_renderbuffer_;
  PFNGLFRAMEBUFFERTEXTUREPROC gl_framebuffer_texture_;
  PFNGLDRAWBUFFERSPROC gl_draw_buffers_;
  PFNGLDELETEBUFFERSPROC gl_delete_buffers_;
  PFNGLGENBUFFERSPROC gl_gen_buffers_;
  PFNGLBINDBUFFERPROC gl_bind_buffer_;
  PFNGLBUFFERDATAPROC gl_buffer_data_;
  PFNGLDELETEPROGRAMPROC gl_delete_program_;
  PFNGLBINDVERTEXARRAYPROC gl_bind_vertex_array_;
  PFNGLDELETEVERTEXARRAYSPROC gl_delete_vertex_arrays_;
  PFNGLGENVERTEXARRAYSPROC gl_gen_vertex_arrays_;
  PFNGLBINDATTRIBLOCATIONPROC gl_bind_attrib_location_;
  PFNGLBUFFERSUBDATAPROC gl_buffer_sub_data_;
  PFNGLVERTEXATTRIBPOINTERPROC gl_vertex_attrib_pointer_;
  PFNGLUSEPROGRAMPROC gl_use_program_;
  PFNGLENABLEVERTEXATTRIBARRAYPROC gl_enable_vertex_attrib_array_;
  PFNGLDISABLEVERTEXATTRIBARRAYPROC gl_disable_vertex_attrib_array_;
  PFNGLUNIFORM1FPROC gl_uniform_1f_;
  PFNGLUNIFORM2FPROC gl_uniform_2f_;
  PFNGLUNIFORM3FPROC gl_uniform_3f_;
  PFNGLUNIFORM4FPROC gl_uniform_4f_;
  PFNGLUNIFORM1IPROC gl_uniform_1i_;
  PFNGLUNIFORM2IPROC gl_uniform_2i_;
  PFNGLUNIFORM3IPROC gl_uniform_3i_;
  PFNGLUNIFORM4IPROC gl_uniform_4i_;
  PFNGLTEXBUFFERPROC gl_tex_buffer_;
  PFNGLUNIFORMMATRIX3X2FVPROC gl_uniform_matrix_3x2_fv_;
  PFNGLUNIFORM3FVPROC gl_uniform_3fv_;
  PFNGLGETUNIFORMLOCATIONPROC gl_get_uniform_location_;
  PFNGLACTIVETEXTUREPROC gl_active_texture_;
  PFNGLGETATTRIBLOCATIONPROC gl_get_attrib_location_;
  PFNGLUNIFORM4FVPROC gl_uniform_4fv_;
  PFNGLUNIFORMMATRIX4FVPROC gl_uniform_matrix_4fv_;
  PFNGLDRAWARRAYSINSTANCEDARBPROC gl_draw_arrays_instanced_arb_;
  PFNGLCREATEPROGRAMPROC gl_create_program_;
  PFNGLCREATESHADERPROC gl_create_shader_;
  PFNGLSHADERSOURCEPROC gl_shader_source_;
  PFNGLCOMPILESHADERPROC gl_compile_shader_;
  PFNGLGETSHADERIVPROC gl_get_shader_iv_;
  PFNGLGETSHADERINFOLOGPROC gl_get_shader_info_log_;
  PFNGLATTACHSHADERPROC gl_attach_shader_;
  PFNGLDETACHSHADERPROC gl_detach_shader_;
  PFNGLDELETESHADERPROC gl_delete_shader_;
  PFNGLGETPROGRAMIVPROC gl_get_programiv_;
  PFNGLLINKPROGRAMPROC gl_link_program_;
  PFNGLGETPROGRAMINFOLOGPROC gl_get_program_info_log_;
  PFNGLDELETERENDERBUFFERSPROC gl_delete_renderbuffers_;
  PFNGLDELETEFRAMEBUFFERSPROC gl_delete_framebuffers_;
  PFNGLFRAMEBUFFERTEXTURE2DPROC gl_framebuffer_texture_2D_;
  PFNGLUNIFORM2FVPROC gl_uniform_2fv_;
};

}

#endif // BUSTA_OPENGLEXTENSIONMANAGER_H
