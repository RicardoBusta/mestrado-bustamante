#ifndef SHADERS_H
#define SHADERS_H

#include <QMap>
#include <QGLShaderProgram>

class Shaders
{
public:
  static Shaders *instance();

  static bool bind(QString shader_name);
  static bool release(QString shader_name);
private:
  Shaders();

  QMap<QString,QGLShaderProgram*> map;

  bool setParameters(const QString &shader_name);

  static Shaders * instance_;
};

#endif // SHADERS_H
