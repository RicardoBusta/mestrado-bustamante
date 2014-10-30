#include "saturn.h"

Saturn::Saturn():
  Object()
{
  model_name = "Sphere";
  texture = ":/texture/texture_saturn.jpg";
  radius = 10;
  draw_orbit= true;
  object_name = "Saturn";
  translation_x_radius = 3000;
  translation_z_radius = 3000;
  translation_step = 0.1f;
}
