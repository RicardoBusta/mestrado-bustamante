#ifndef SCENE_BONFIRE_H
#define SCENE_BONFIRE_H

#include "programs/CG1/opengl/scene.h"

class SceneBonfire : public Scene
{
  Q_OBJECT
public:
  explicit SceneBonfire(QObject *parent=0);
  virtual ~SceneBonfire();

private:
  void setup_spec();
  virtual void buildControlWidget();
};

#endif // SCENE_BONFIRE_H
