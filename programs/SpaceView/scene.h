#ifndef SCENE_H
#define SCENE_H

#include "object.h"

#include <QVector>

#include "slidepage.h"

class Scene
{
public:
  Scene();

  void init();
  void draw();
  void step();

  Object *light_object;

  Object *camera_object;
  QVector3D camera_position;

  float camera_timer;

  QVector<Object*> objects;

  float zoom;
  bool draw_orbit;

  int current_page;
  QVector<SlidePage*> focus;
};

#endif // SCENE_H
