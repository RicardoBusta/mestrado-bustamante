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

}
