#include "mercury.h"

Mercury::Mercury():
  Object()
{
  model_name = "Sphere";
  texture = ":/texture/texture_mercury.jpg";
  radius = 10;
  draw_orbit= true;
  object_name = "Mercury";
  translation_x_radius = 500;
  translation_z_radius = 500;
  translation_step = 0.1f;
}
