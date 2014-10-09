#ifndef SCENE_FUR_H
#define SCENE_FUR_H

#include "programs/CG1/opengl/scene.h"

class SceneFur : public Scene
{
  Q_OBJECT
public:
  explicit SceneFur(QObject *parent=0);
  virtual ~SceneFur();
private:
  void setup_spec();
  virtual void buildControlWidget();

  float speed_;
  float gravity_;

  void calcScene();

  QVector< Object * > fur_layer_;

private slots:
  void changeGravity(double g);
  void changeSpeed(double s);
  void toggleFur(bool f);
};

#endif // SCENE_FUR_H
