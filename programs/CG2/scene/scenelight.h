#ifndef SCENELIGHT_H
#define SCENELIGHT_H

#include "structures.h"

class SceneLight
{
public:
  SceneLight();
  SceneLight(Ric::Vector p, Ric::LightComponent c, double radius);
  SceneLight(const SceneLight *l, const Ric::Matrix4x4 *transform);
  ~SceneLight();

  double radius;
  Ric::Vector position;
  Ric::LightComponent material;
};

#endif // SCENELIGHT_H
