#include "openglextensionshortcut.h"

void texImage3D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *data)
{
  Busta::OpenGL::instance()->texImage3D(target,level,internalFormat,width,height,depth,border,format,type,data);
}

void glGenFramebuffers(GLsizei n, GLuint *ids)
{
  Busta::OpenGL::instance()->glGenFramebuffers(n,ids);
}

void glBindFramebuffer(GLenum target, GLuint framebuffer)
{
  Busta::OpenGL::instance()->glBindFramebuffer(target,framebuffer);
}

GLenum glCheckFramebufferStatus(GLenum target)
{
  Busta::OpenGL::instance()->glCheckFramebufferStatus(target);
}

void glGenRenderbuffers(GLsizei n, GLuint *renderbuffers)
{
  Busta::OpenGL::instance()->glGenRenderbuffers(n,renderbuffers);
}

void glBindRenderbuffer(GLenum target, GLuint renderbuffer)
{
  Busta::OpenGL::instance()->glBindRenderbuffer(target,renderbuffer);
}

void glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
{
  Busta::OpenGL::instance()->glRenderbufferStorage(target,internalformat,width,height);
}

void glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
  Busta::OpenGL::instance()->glFramebufferRenderbuffer(target,attachment,renderbuffertarget,renderbuffer);
}

void glFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level)
{
  Busta::OpenGL::instance()->glFramebufferTexture(target,attachment,texture,level);
}

void glDrawBuffers(GLsizei n, const GLenum *bufs)
{
  Busta::OpenGL::instance()->glDrawBuffers(n,bufs);
}

void glDeleteBuffers(GLsizei n, const GLuint *buffers)
{
  Busta::OpenGL::instance()->glDeleteBuffers(n,buffers);
}

void glGenBuffers(GLsizei n, GLuint *buffers)
{
  Busta::OpenGL::instance()->glGenBuffers(n,buffers);
}

void glBindBuffer(GLenum target, GLuint buffer)
{
  Busta::OpenGL::instance()->glBindBuffer(target,buffer);
}

void glBufferData(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage)
{
  Busta::OpenGL::instance()->glBufferData(target,size,data,usage);
}

void glDeleteProgram(GLuint program)
{
  Busta::OpenGL::instance()->glDeleteProgram(program);
}

void glBindVertexArray(GLuint array)
{
  Busta::OpenGL::instance()->glBindVertexArray(array);
}

void glDeleteVertexArrays(GLsizei n, const GLuint *arrays)
{
  Busta::OpenGL::instance()->glDeleteVertexArrays(n,arrays);
}

void glGenVertexArrays(GLsizei n, GLuint *arrays)
{
  Busta::OpenGL::instance()->glGenVertexArrays(n,arrays);
}

void glBindAttribLocation(GLuint program, GLuint index, const GLchar *name)
{
  Busta::OpenGL::instance()->glBindAttribLocation(program,index,name);
}

void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data)
{
  Busta::OpenGL::instance()->glBufferSubData(target,offset,size,data);
}

void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer)
{
  Busta::OpenGL::instance()->glVertexAttribPointer(index,size,type,normalized,stride,pointer);
}

void glUseProgram(GLuint program)
{
  Busta::OpenGL::instance()->glUseProgram(program);
}

void glEnableVertexAttribArray(GLuint index)
{
  Busta::OpenGL::instance()->glEnableVertexAttribArray(index);
}

void glDisableVertexAttribArray(GLuint index)
{
  Busta::OpenGL::instance()->glDisableVertexAttribArray(index);
}

void glUniform1f(GLint location, GLfloat v0)
{
  Busta::OpenGL::instance()->glUniform1f(location,v0);
}

void glUniform2f(GLint location, GLfloat v0, GLfloat v1)
{
  Busta::OpenGL::instance()->glUniform2f(location,v0,v1);
}

void glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
  Busta::OpenGL::instance()->glUniform3f(location,v0,v1,v2);
}

void glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
  Busta::OpenGL::instance()->glUniform4f(location,v0,v1,v2,v3);
}

void glUniform1i(GLint location, GLint v0)
{
  Busta::OpenGL::instance()->glUniform1i(location,v0);
}

void glUniform2i(GLint location, GLint v0, GLint v1)
{
  Busta::OpenGL::instance()->glUniform2i(location,v0,v1);
}

void glUniform3i(GLint location, GLint v0, GLint v1, GLint v2)
{
  Busta::OpenGL::instance()->glUniform3i(location,v0,v1,v2);
}

void glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
{
  Busta::OpenGL::instance()->glUniform4i(location,v0,v1,v2,v3);
}

void glTexBuffer(GLenum target, GLenum internalFormat, GLuint buffer)
{
  Busta::OpenGL::instance()->glTexBuffer(target,internalFormat,buffer);
}

void glUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
  Busta::OpenGL::instance()->glUniformMatrix3x2fv(location,count,transpose,value);
}

void glUniform3fv(GLint location, GLsizei count, const GLfloat *value)
{
  Busta::OpenGL::instance()->glUniform3fv(location,count,value);
}

GLint glGetUniformLocation(GLuint program, const GLchar *name)
{
  Busta::OpenGL::instance()->glGetUniformLocation(program,name);
}

void glActiveTexture(GLenum texture)
{
  Busta::OpenGL::instance()->glActiveTexture(texture);
}

GLint glGetAttribLocation(GLuint program, const GLchar *name)
{
  Busta::OpenGL::instance()->glGetAttribLocation(program,name);
}

void glUniform4fv(GLint location, GLsizei count, const GLfloat *value)
{
  Busta::OpenGL::instance()->glUniform4fv(location,count,value);
}

void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
  Busta::OpenGL::instance()->glUniformMatrix4fv(location,count,transpose,value);
}

void glDrawArraysInstancedARB(GLenum mode, GLint first, GLsizei count, GLsizei primcount)
{
  Busta::OpenGL::instance()->glDrawArraysInstancedARB(mode,first,count,primcount);
}

GLuint glCreateProgram()
{
  return Busta::OpenGL::instance()->glCreateProgram();
}

GLuint glCreateShader(GLenum shaderType)
{
  return Busta::OpenGL::instance()->glCreateShader(shaderType);
}

void glShaderSource(GLuint shader, GLsizei count, const GLchar **string, const GLint *length)
{
  Busta::OpenGL::instance()->glShaderSource(shader,count,string,length);
}

void glCompileShader(GLuint shader)
{
  Busta::OpenGL::instance()->glCompileShader(shader);
}

void glGetShaderiv(GLuint shader, GLenum pname, GLint *params)
{
  Busta::OpenGL::instance()->glGetShaderiv(shader,pname,params);
}

void glGetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei *length, GLchar *infoLog)
{
  Busta::OpenGL::instance()->glGetShaderInfoLog(shader,maxLength,length,infoLog);
}

void glAttachShader(GLuint program, GLuint shader)
{
  Busta::OpenGL::instance()->glAttachShader(program,shader);
}

void glDetachShader(GLuint program, GLuint shader)
{
  Busta::OpenGL::instance()->glDetachShader(program,shader);
}

void glDeleteShader(GLuint shader)
{
  Busta::OpenGL::instance()->glDeleteShader(shader);
}

void glGetProgramiv(GLuint program, GLenum pname, GLint *params)
{
  Busta::OpenGL::instance()->glGetProgramiv(program,pname,params);
}

void glLinkProgram(GLuint program)
{
  Busta::OpenGL::instance()->glLinkProgram(program);
}

void glGetProgramInfoLog(GLuint program, GLsizei maxLength, GLsizei *length, GLchar *infoLog)
{
  Busta::OpenGL::instance()->glGetProgramInfoLog(program,maxLength,length,infoLog);
}

void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
  Busta::OpenGL::instance()->glFramebufferTexture2D(target,attachment,textarget,texture,level);
}

void glDeleteRenderbuffers(GLsizei n, const GLuint *renderbuffers)
{
  Busta::OpenGL::instance()->glDeleteRenderbuffers(n,renderbuffers);
}

void glDeleteFramebuffers(GLsizei n, GLuint *framebuffers)
{
  Busta::OpenGL::instance()->glDeleteFramebuffers(n,framebuffers);
}

void glUniform2fv(GLint location, GLsizei count, const GLfloat *value)
{
  Busta::OpenGL::instance()->glUniform2fv(location,count,value);
}
