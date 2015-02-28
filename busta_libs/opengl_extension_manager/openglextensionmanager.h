#ifndef BUSTA_OPENGLEXTENSIONMANAGER_H
#define BUSTA_OPENGLEXTENSIONMANAGER_H

#include <QtOpenGL>
#include "openglextensiontypedef.h"

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

private:
  OpenGL();

  static OpenGL * instance_;

  PFGLTEXIMAGE3D gl_tex_image_3d_;
  PFGLGENFRAMEBUFFERS gl_gen_framebuffers_;
  PFGLBINDFRAMEBUFFER gl_bind_framebuffer_;
  PFGLCHECKFRAMEBUFFERSTATUS gl_check_framebuffer_status_;
  PFGLGENRENDERBUFFERS gl_gen_renderbuffers_;
  PFGLRENDERBUFFERSTORAGE gl_renderbuffer_storage_;
  PFGLBINDRENDERBUFFER gl_bind_renderbuffer_;
  PFGLFRAMEBUFFERRENDERBUFFER gl_framebuffer_renderbuffer_;
  PFGLFRAMEBUFFERTEXTURE gl_framebuffer_texture_;
  PFGLDRAWBUFFERS gl_draw_buffers_;
};

}

#endif // BUSTA_OPENGLEXTENSIONMANAGER_H
