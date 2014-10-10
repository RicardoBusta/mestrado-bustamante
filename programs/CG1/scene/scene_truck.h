#ifndef SCENE_TRUCK_H
#define SCENE_TRUCK_H

#include "programs/CG1/opengl/scene.h"

class SceneTruck : public Scene
{
  Q_OBJECT
public:
  SceneTruck(QObject *parent=0);

  virtual void applyCameraConstraint();
private:
  void setup_spec();
  virtual void buildControlWidget();

  bool camera_constraint_;
private slots:
  void toggleCameraConstraint(bool v);

};

#endif // SCENE_TRUCK_H
