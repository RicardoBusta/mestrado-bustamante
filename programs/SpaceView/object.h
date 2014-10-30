#ifndef OBJECT_H
#define OBJECT_H

#include <QString>

#include <QVector3D>

class Object
{
public:
  Object();

  QString object_name;

  QString model_name;
  QString texture;

  QVector3D pos;

  float radius;

  bool emit_light;

  //orbit
  float translation_x_radius;
  float translation_z_radius;
  Object *orbit_center;
  bool orbit;
  bool draw_orbit;

  // step
  float rotation_angle_step;
  float translation_step;

  float tilt;

  // current
  float current_rotation_angle;
  float current_translation_angle;

  void draw();
  void drawOrbit();
  void step();
};

#endif // OBJECT_H
