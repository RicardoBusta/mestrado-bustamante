#ifndef SCENE_MULTICUBES_H
#define SCENE_MULTICUBES_H

#include "opengl/scene.h"

class SceneMultiCubes : public Scene
{
  Q_OBJECT
public:
  SceneMultiCubes(QObject *parent=0);

private:
  void setup_spec();
  virtual void buildControlWidget();
};

#endif // SCENE_MULTICUBES_H
