#include "material.h"

#ifdef _WIN32
#include <Windows.h>
#endif
#include <GL/gl.h>
#include <QDebug>

namespace Ric{

Material::Material(const Color &diffuse, const Color &specular, const Color &ambient, const double &shininess)
  : diffuse_(diffuse),
    specular_(specular),
    ambient_(ambient),
    shininess_(shininess),
    refraction_(1),
    transparency_(0),
    reflection_(0),
    has_texture_(false),
    environment_map_(false),
    environment_(false),
    isLight_(false)
{
}

Material Material::Create(const unsigned int &color)
{
  return Material(
        Ric::Color(color),
        Ric::Color(0xffffffff),
        Ric::Color(color),
        100
        );
}

Material Material::CreateWithReflection(const unsigned int &color,const unsigned int &ref)
{
  Material m(
        Ric::Color(color),
        Ric::Color(0xffffffff),
        Ric::Color(color),
        100
        );
  m.SetReflection(ref);

  return m;
}

Ric::Color Material::diffuse() const
{
  return diffuse_;
}


Ric::Color Material::specular() const
{
  return specular_;
}


Ric::Color Material::ambient() const
{
  return ambient_;
}

double Material::transparency() const
{
  return transparency_;
}

double Material::reflection() const
{
  return reflection_;
}

double Material::refraction() const
{
  return refraction_;
}

double Material::shininess() const
{
  return shininess_;
}

bool Material::has_texture() const
{
  return has_texture_;
}

bool Material::has_normal_map() const
{
  return true;
}

bool Material::environment() const
{
  return environment_;
}

bool Material::environment_map() const
{
  return environment_map_;
}

bool Material::isLight() const
{
  return isLight_;
}

void Material::SetAmbient(const double &r, const double &g, const double &b)
{
  ambient_ = Ric::Color(r,g,b);
}

void Material::SetDiffuse(const double &r, const double &g, const double &b)
{
  diffuse_ = Ric::Color(r,g,b);
}

void Material::SetSpecular(const double &r, const double &g, const double &b)
{
  specular_ = Ric::Color(r,g,b);
}

void Material::SetReflection(const double &r)
{
  reflection_ = r;
}

void Material::SetTransparency(const double &t)
{
  transparency_ = t;
}

void Material::SetRefraction(const double &r)
{
  refraction_ = r;
}

void Material::SetEnviro(const bool &b)
{
  qDebug() << "set_enviro";
  environment_ = b;
}

void Material::SetEnviroMap(const bool &b)
{
  environment_map_ = b;
}

void Material::SetIsLight(const bool &b)
{
  isLight_ = b;
}

Material Material::operator=(Material m)
{
  this->ambient_ = m.ambient_;
  this->diffuse_ = m.diffuse_;
  this->specular_ = m.specular_;
  this->shininess_ = m.shininess_;
  this->transparency_ = m.transparency_;
  this->has_texture_ = m.has_texture_;
  this->diffuse_texture_ = m.diffuse_texture_;
  this->reflection_ = m.reflection_;
  this->refraction_ = m.refraction_;
  this->environment_map_ = m.environment_map_;
  this->environment_= m.environment_;
  this->isLight_ = m.isLight_;
  return *this;
}

void Material::SetDifTexture( const std::string &diffuse_texture)
{
  has_texture_ = true;
  diffuse_texture_ = diffuse_texture;
}

std::string Material::GetDifTexture() const
{
  return diffuse_texture_;
}

void Material::GlSet()
{
  //    if(has_texture_){
  //        glEnable(GL_TEXTURE_2D);
  //    }else{
  //        glDisable(GL_TEXTURE_2D);
  //    }
  //  glColor3f(1,0,0);
  //  GLfloat ambient[] = {ambient_.r(),ambient_.g(),ambient_.b(),1.0f};
  //  GLfloat diffuse[] = {diffuse_.r(),diffuse_.g(),diffuse_.b(),1.0f};
  //  GLfloat specular[] = {specular_.r(),specular_.g(),specular_.b(),1.0f};
  //  GLfloat shininess[] = {shininess_};
  //    GLfloat ambient[] = {0,0,0,1.0f};
  //    GLfloat diffuse[] = {1,0,0,1.0f};
  //    GLfloat specular[] = {1,1,1,1.0f};
  //    qDebug() << diffuse_.r() << diffuse_.g() << diffuse_.b();
  //    GLfloat shininess[] = {100};
  //  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambient);
  //  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,ambient);
  //  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diffuse);
  //  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular);
  //  glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shininess);
  //  qDebug() << glGetError();
  glColor3f(diffuse_.r(),diffuse_.g(),diffuse_.b());
}

LightComponent::LightComponent(const Color &diffuse, const Color &specular, const Color &ambient)
  : diffuse_(diffuse),
    specular_(specular),
    ambient_(ambient)
{

}

LightComponent LightComponent::Create(const unsigned int &color)
{
  return LightComponent(
        Ric::Color(color),
        Ric::Color(0xffffffff),
        Ric::Color(color)
        );
}

Color LightComponent::diffuse() const
{
  return diffuse_;
}

Color LightComponent::specular() const
{
  return specular_;
}

Color LightComponent::ambient() const
{
  return ambient_;
}

LightComponent LightComponent::operator=(LightComponent l)
{
  this->diffuse_ = l.diffuse_;
  this->specular_ = l.specular_;
  this->ambient_ = l.ambient_;
  return *this;
}





} // namespace
