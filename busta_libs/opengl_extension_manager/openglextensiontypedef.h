#ifndef OPENGL_TYPEDEF_H
#define OPENGL_TYPEDEF_H

#include <QtOpenGL>

typedef void (*PFGLTEXIMAGE3D)(
    GLenum ,
    GLint ,
    GLint ,
    GLsizei ,
    GLsizei ,
    GLsizei ,
    GLint ,
    GLenum ,
    GLenum ,
    const GLvoid *
    );

#ifndef GL_TEXTURE_WRAP_R
#define GL_TEXTURE_WRAP_R 0x8072
#endif

#ifndef GL_TEXTURE_3D
#define GL_TEXTURE_3D 0x806F
#endif

#endif // OPENGL_TYPEDEF_H
