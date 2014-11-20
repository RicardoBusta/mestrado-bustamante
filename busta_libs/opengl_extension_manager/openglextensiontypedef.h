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
    GLenum ,    // target
    GLint ,     // level
    GLint ,     // internalFormat
    GLsizei ,   // width
    GLsizei ,   // height
    GLsizei ,   // depth
    GLint ,     // border
    GLenum ,    // format
    GLenum ,    // type
    const GLvoid * // data
    );

#ifndef GL_TEXTURE_WRAP_R
#define GL_TEXTURE_WRAP_R 0x8072
#endif

#ifndef GL_TEXTURE_3D
#define GL_TEXTURE_3D 0x806F
#endif

#endif // OPENGL_TYPEDEF_H
