#ifndef SCENE_DONUT_H
#define SCENE_DONUT_H

#include "programs/CG1/opengl/scene.h"

class SceneDonut : public Scene
{
  Q_OBJECT
public:
  explicit SceneDonut(QObject *parent=0);
  virtual ~SceneDonut();
private:
  void setup_spec();
  virtual void buildControlWidget();
};

#endif // SCENE_DONUT_H
