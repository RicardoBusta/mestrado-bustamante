#ifndef OPENGL_TYPEDEF_H
#define OPENGL_TYPEDEF_H

#include <QtOpenGL>

#if defined(_WIN32)
#define GL_EXT_ENTRY
#define GL_EXT_CALL     __stdcall
#define GL_CALLBACK     __stdcall
#else
#define GL_EXT_ENTRY
#define GL_EXT_CALL
#define GL_CALLBACK
#endif

typedef GL_EXT_ENTRY void (GL_EXT_CALL * PFGLTEXIMAGE3D)(
    GLenum ,      // target
    GLint ,       // level
    GLint ,       // internalFormat
    GLsizei ,     // width
    GLsizei ,     // height
    GLsizei ,     // depth
    GLint ,       // border
    GLenum ,      // format
    GLenum ,      // type
    const GLvoid * // data
    );

typedef GL_EXT_ENTRY void (GL_EXT_CALL * PFGLGENFRAMEBUFFERS)(
    GLsizei , // n
    GLuint *  // ids
    );

typedef GL_EXT_ENTRY void (GL_EXT_CALL * PFGLBINDFRAMEBUFFER)(
    GLenum, // target
    GLuint  // framebuffer
    );

typedef GL_EXT_ENTRY void (GL_EXT_CALL * PFGLGENRENDERBUFFERS)(
    GLsizei, // n
    GLuint * // renderbuffers
    );

typedef GL_EXT_ENTRY void (GL_EXT_CALL * PFGLRENDERBUFFERSTORAGE)(
    GLenum,  // target
    GLenum,  // internalformat
    GLsizei, // width
    GLsizei  // height
    );

typedef GL_EXT_ENTRY void (GL_EXT_CALL * PFGLFRAMEBUFFERRENDERBUFFER)(
    GLenum, // target
    GLenum, // attachment
    GLenum, // renderbuffertarget
    GLuint  // renderbuffer
    );

typedef GL_EXT_ENTRY void (GL_EXT_CALL * PFGLFRAMEBUFFERTEXTURE)(
    GLenum, // target
    GLenum, // attachment
    GLuint, // texture
    GLint   // level
    );

typedef GL_EXT_ENTRY void (GL_EXT_CALL * PFGLDRAWBUFFERS)(
    GLsizei,       // n
    const GLenum * //bufs
    );

typedef GL_EXT_ENTRY GLenum (GL_EXT_CALL * PFGLCHECKFRAMEBUFFERSTATUS)(
    GLenum // target
    );

typedef GL_EXT_ENTRY void (GL_EXT_CALL * PFGLBINDRENDERBUFFER)(
    GLenum, // target
    GLuint renderbuffer
    );

#ifndef GL_TEXTURE_WRAP_R
#define GL_TEXTURE_WRAP_R 0x8072
#endif

#ifndef GL_TEXTURE_3D
#define GL_TEXTURE_3D 0x806F
#endif

#endif // OPENGL_TYPEDEF_H
