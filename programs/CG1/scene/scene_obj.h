#ifndef SCENE_OBJ_H
#define SCENE_OBJ_H

#include "programs/CG1/opengl/scene.h"

class SceneObj : public Scene
{
  Q_OBJECT
public:
  explicit SceneObj(QObject *parent=0);

private:
  void buildControlWidget();

private slots:
  void loadObjFile();
};

#endif // SCENE_OBJ_H
