#ifndef OPENGLEXTENSIONSHORTCUT_H
#define OPENGLEXTENSIONSHORTCUT_H

#include "openglextensionmanager.h"

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

#endif // OPENGLEXTENSIONSHORTCUT_H
