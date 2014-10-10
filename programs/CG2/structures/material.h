#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"
#include "string"

namespace Ric{

class LightComponent{
public:
  LightComponent(const Color &diffuse = Ric::Color(), const Color &specular = Ric::Color(), const Color &ambient = Ric::Color());

  static LightComponent Create(const unsigned int &color);

  Ric::Color diffuse() const;
  Ric::Color specular() const;
  Ric::Color ambient() const;

  LightComponent operator=(LightComponent l);
private:
  Ric::Color diffuse_; //< diffuse light intensity
  Ric::Color specular_; //< specular light intensity
  Ric::Color ambient_; //< ambient light intensity
};

class Material
{
public:
  Material(const Color &diffuse = Ric::Color(), const Color &specular = Ric::Color(), const Color &ambient = Ric::Color(), const double &shininess = 100);

  static Material Create(const unsigned int &color);
  static Material CreateWithReflection(const unsigned int &color,const unsigned int &ref);

  Ric::Color diffuse() const;
  Ric::Color specular() const;
  Ric::Color ambient() const;
  Ric::Color reflected() const;
  Ric::Color transmitted() const;
  double transparency() const;
  double reflection() const;
  double refraction() const;
  double shininess() const;

  bool has_texture() const;
  bool has_normal_map() const;

  bool environment() const;
  bool environment_map() const;

  bool isLight() const;

  void SetAmbient(const double &r, const double &g, const double &b);
  void SetDiffuse(const double &r, const double &g, const double &b);
  void SetSpecular(const double &r, const double &g, const double &b);
  void SetReflection(const double &r);
  void SetTransparency(const double &t);
  void SetRefraction(const double &r);
  void SetEnviro(const bool &b);
  void SetEnviroMap(const bool &b);
  void SetIsLight(const bool &b);

  Material operator=(Material m);

  void SetDifTexture(const std::string &diffuse_texture);

  std::string GetDifTexture() const;

  void GlSet();

private:
  Ric::Color diffuse_; //< diffuse light intensity
  Ric::Color specular_; //< specular light intensity
  Ric::Color ambient_; //< ambient light intensity
  double shininess_; //< shininess

  double refraction_;
  double transparency_; //< dissolve or transparency
  double reflection_;

  bool has_texture_;
  std::string diffuse_texture_;
  bool environment_map_;
  bool environment_;

  bool isLight_;
};

} // namespace

#endif // MATERIAL_H
