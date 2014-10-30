#include "mars.h"

Mars::Mars():
  Object()
{
  model_name = "Sphere";
  texture = ":/texture/texture_mars.jpg";
  radius = 10;
  draw_orbit= true;
  object_name = "Mars";
  translation_x_radius = 2000;
  translation_z_radius = 2000;
  translation_step = 0.1;
}
