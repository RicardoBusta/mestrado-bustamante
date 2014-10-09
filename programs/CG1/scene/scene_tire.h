#ifndef SCENE_TIRE_H
#define SCENE_TIRE_H

#include "programs/CG1/opengl/scene.h"

class SceneTire : public Scene
{
  Q_OBJECT
public:
  explicit SceneTire(QObject *parent=0);
  virtual ~SceneTire();
private:
  void setup_spec();
  virtual void buildControlWidget();
};

#endif // SCENE_TIRE_H
