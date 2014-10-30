#include "uranus.h"

Uranus::Uranus():
  Object()
{
  model_name = "Sphere";
  texture = ":/texture/texture_uranus.jpg";
  radius = 10;
  draw_orbit= true;
  object_name = "Uranus";
  translation_x_radius = 4000;
  translation_z_radius = 4000;
  translation_step = 0.1;
}
