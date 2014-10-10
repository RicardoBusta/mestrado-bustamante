#include "shaders.h"

#include "programs/CG1/utils/options.h"

Shaders * Shaders::instance_ = NULL;

Shaders::Shaders()
{
}

bool Shaders::setParameters(const QString &shader_name)
{
  Q_UNUSED(shader_name);
  bool ok = true;
//  int options_location = map[shader_name]->attributeLocation("gl_TexCoord[0]");
//  qDebug() << options_location;
//  ok &= map[shader_name]->setUniformValue(options_location,QVector4D(1,0,0,0));

  return ok;
}

Shaders *Shaders::instance()
{
  if(NULL == instance_){
    instance_ = new Shaders;
  }
  return instance_;
}

bool Shaders::bind(QString shader_name)
{
  if(!Options::instance()->get_option("check_shader")) return true;

  bool ok = true;

  if(instance_->map.contains(shader_name)){
    if(NULL == instance_->map[shader_name]){
      ok = instance_->map[shader_name]->bind();
//      instance_->setParameters(shader_name);
      return ok;
    }else{
      return false;
    }
  }

  instance_->map.insert(shader_name,new QGLShaderProgram);
  qDebug() << "Opening shader file:" << ":/shaders/"+shader_name+".vsh";
  ok &= instance_->map[shader_name]->addShaderFromSourceFile(QGLShader::Vertex,":/shaders/"+shader_name+".vsh");
  qDebug() << "Opening shader file:" << ":/shaders/"+shader_name+".fsh";
  ok &= instance_->map[shader_name]->addShaderFromSourceFile(QGLShader::Fragment,":/shaders/"+shader_name+".fsh");
  ok &= instance_->map[shader_name]->link();
  qDebug() << "ok?" << ok;
  if(!ok){
    delete instance_->map[shader_name];
    instance_->map.remove(shader_name);
    instance_->map.insert(shader_name,NULL);
  }else{
    ok = instance_->map[shader_name]->bind();
//    instance_->setParameters(shader_name);
  }
  return ok;
}

bool Shaders::release(QString shader_name)
{
  if(!Options::instance()->get_option("check_shader")) return true;

  if( instance_->map.contains(shader_name) && (NULL != instance_->map[shader_name]) ){
    instance_->map[shader_name]->release();
    return true;
  }else{
    return false;
  }
}
