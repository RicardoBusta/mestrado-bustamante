#ifndef BUSTA_OPENGLEXTENSIONMANAGER_H
#define BUSTA_OPENGLEXTENSIONMANAGER_H

#include <QtOpenGL>
#include "openglextensiontypedef.h"

namespace Busta{

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

}

#endif // BUSTA_OPENGLEXTENSIONMANAGER_H
