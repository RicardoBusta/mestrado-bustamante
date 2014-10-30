#include "pluto.h"

Pluto::Pluto():
  Object()
{
  model_name = "Sphere";
  texture = ":/texture/texture_pluto.jpg";
  radius = 10;
  draw_orbit= true;
  object_name = "Pluto";
  translation_x_radius = 4500;
  translation_z_radius = 4500;
  translation_step = 0.1f;
}
