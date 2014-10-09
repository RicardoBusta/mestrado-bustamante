#ifndef OPENGL_H
#define OPENGL_H

#include <QtOpenGL>
#include "opengl_typedef.h"

class OpenGL
{
public:
  static OpenGL * instance();

  void texImage3D(GLenum target,
                    GLint level,
                    GLint internalFormat,
                    GLsizei width,
                    GLsizei height,
                    GLsizei depth,
                    GLint border,
                    GLenum format,
                    GLenum type,
                    const GLvoid * data);
private:
  OpenGL();

  static OpenGL * instance_;

  PFGLTEXIMAGE3D gl_tex_image_3d_;
};

#endif // OPENGL_H
