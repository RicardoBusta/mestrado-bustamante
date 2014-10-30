#include "neptune.h"

Neptune::Neptune():
  Object()
{
  model_name = "Sphere";
  texture = ":/texture/texture_neptune.jpg";
  radius = 10;
  draw_orbit= true;
  object_name = "Neptune";
  translation_x_radius = 3500;
  translation_z_radius = 3500;
  translation_step = 0.1f;
}
