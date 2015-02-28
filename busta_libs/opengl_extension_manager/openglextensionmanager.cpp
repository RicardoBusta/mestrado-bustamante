#include "openglextensionmanager.h"

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

void OpenGL::texImage3D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *data)
{
#ifdef _WIN32
  if(gl_tex_image_3d_ == NULL){
    gl_tex_image_3d_ = (PFGLTEXIMAGE3D)wglGetProcAddress("glTexImage3D");
    qDebug() << "Loaded texImage3D:" << gl_tex_image_3d_;
  }
  if(gl_tex_image_3d_ == NULL){
    qDebug() << "Binding fail";
    return;
  }
  gl_tex_image_3d_(target,level,internalFormat,width,height,depth,border,format,type,data);
#else // _WIN32
  glTexImage3D(target,level,internalFormat,width,height,depth,border,format,type,data);
#endif
}

void OpenGL::glGenFramebuffers(GLsizei n, GLuint *ids)
{
#ifdef _WIN32
  if(gl_gen_framebuffers_ == NULL){
    gl_gen_framebuffers_ = (PFGLGENFRAMEBUFFERS)wglGetProcAddress("glGenFramebuffers");
  }
  if(gl_gen_framebuffers_ == NULL){
    qDebug() << "Binding fail";
    return;
  }
  gl_gen_framebuffers_(n,ids);
#else // _WIN32
  glGenFramebuffers(n,ids);
#endif
}

void OpenGL::glBindFramebuffer(GLenum target, GLuint framebuffer)
{
#ifdef _WIN32
  if(gl_bind_framebuffer_ == NULL){
    gl_bind_framebuffer_ = (PFGLBINDFRAMEBUFFER)wglGetProcAddress("glBindFramebuffer");
  }
  if(gl_bind_framebuffer_ == NULL){
    qDebug() << "Binding fail";
    return;
  }
  gl_bind_framebuffer_(target,framebuffer);
#else // _WIN32
  glBindFramebuffer(target,framebuffer);
#endif
}

GLenum OpenGL::glCheckFramebufferStatus(GLenum target)
{
#ifdef _WIN32
  if(gl_check_framebuffer_status_ == NULL){
    gl_check_framebuffer_status_ = (PFGLCHECKFRAMEBUFFERSTATUS)wglGetProcAddress("glCheckFramebufferStatus");
  }
  if(gl_check_framebuffer_status_ == NULL){
    qDebug() << "Binding fail";
    return GL_INVALID_ENUM;
  }
  return gl_check_framebuffer_status_(target);
#else // _WIN32
  return glCheckFramebufferStatus(target);
#endif
}

void OpenGL::glGenRenderbuffers(GLsizei n, GLuint *renderbuffers)
{
#ifdef _WIN32
  if(gl_gen_renderbuffers_ == NULL){
    gl_gen_renderbuffers_ = (PFGLGENRENDERBUFFERS)wglGetProcAddress("glGenRenderbuffers");
  }
  if(gl_gen_renderbuffers_ == NULL){
    qDebug() << "Binding fail";
    return;
  }
  gl_gen_renderbuffers_(n,renderbuffers);
#else // _WIN32
  glGenRenderbuffers(n,renderbuffers);
#endif
}

void OpenGL::glBindRenderbuffer(GLenum target, GLuint renderbuffer)
{
#ifdef _WIN32
  if(gl_bind_renderbuffer_ == NULL){
    gl_bind_renderbuffer_ = (PFGLBINDRENDERBUFFER)wglGetProcAddress("glBindRenderbuffer");
  }
  if(gl_bind_renderbuffer_ == NULL){
    qDebug() << "Binding fail";
    return;
  }
  gl_bind_renderbuffer_(target,renderbuffer);
#else // _WIN32
  glBindRenderbuffer(target,renderbuffer);
#endif
}

void OpenGL::glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
{
#ifdef _WIN32
  if(gl_renderbuffer_storage_ == NULL){
    gl_renderbuffer_storage_ = (PFGLRENDERBUFFERSTORAGE)wglGetProcAddress("glRenderbufferStorage");
  }
  if(gl_renderbuffer_storage_ == NULL){
    qDebug() << "Binding fail";
    return;
  }
  gl_renderbuffer_storage_(target,internalformat,width,height);
#else // _WIN32
  glRenderbufferStorage(target,internalformat,width,height);
#endif
}

void OpenGL::glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
#ifdef _WIN32
  if(gl_framebuffer_renderbuffer_ == NULL){
    gl_framebuffer_renderbuffer_ = (PFGLFRAMEBUFFERRENDERBUFFER)wglGetProcAddress("glFramebufferRenderbuffer");
  }
  if(gl_framebuffer_renderbuffer_ == NULL){
    qDebug() << "Binding fail";
    return;
  }
  gl_framebuffer_renderbuffer_(target,attachment,renderbuffertarget,renderbuffer);
#else // _WIN32
  glFramebufferRenderbuffer(target,attachment,renderbuffertarget,renderbuffer);
#endif
}

void OpenGL::glFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level)
{
#ifdef _WIN32
  if(gl_framebuffer_texture_ == NULL){
    gl_framebuffer_texture_ = (PFGLFRAMEBUFFERTEXTURE)wglGetProcAddress("glFramebufferTexture");
  }
  if(gl_framebuffer_texture_ == NULL){
    qDebug() << "Binding fail";
    return;
  }
  gl_framebuffer_texture_(target,attachment,texture,level);
#else // _WIN32
  glFramebufferTexture(target,attachment,texture,level);
#endif
}

void OpenGL::glDrawBuffers(GLsizei n, const GLenum *bufs)
{
#ifdef _WIN32
  if(gl_draw_buffers_ == NULL){
    gl_draw_buffers_ = (PFGLDRAWBUFFERS)wglGetProcAddress("glDrawBuffers");
  }
  if(gl_draw_buffers_ == NULL){
    qDebug() << "Binding fail";
    return;
  }
  gl_draw_buffers_(n,bufs);
#else // _WIN32
  glDrawBuffers(target,attachment,renderbuffertarget,renderbuffer);
#endif
}

}
