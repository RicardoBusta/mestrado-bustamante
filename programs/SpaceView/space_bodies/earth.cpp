#include "earth.h"

Earth::Earth():
  Object()
{
  model_name = "Sphere";
  texture = ":/texture/texture_earth.jpg";
  radius = 1;
  draw_orbit= true;
  object_name = "Earth";
  translation_x_radius = 1500;
  translation_z_radius = 1500;
  translation_step = 0.1;
}
