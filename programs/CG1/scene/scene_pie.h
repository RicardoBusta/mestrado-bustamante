#ifndef SCENE_PIE_H
#define SCENE_PIE_H

#include "programs/CG1/opengl/scene.h"

class ScenePie : public Scene
{
  Q_OBJECT
public:
  explicit ScenePie(QObject *parent=0);
  virtual ~ScenePie();
private:
  void setup_spec();
  virtual void buildControlWidget();
};

#endif // SCENE_PIE_H
