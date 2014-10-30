#include "jupiter.h"

Jupiter::Jupiter():
  Object()
{
  model_name = "Sphere";
  texture = ":/texture/texture_jupiter.jpg";
  radius = 10;
  draw_orbit= true;
  object_name = "Jupiter";
  translation_x_radius = 2500;
  translation_z_radius = 2500;
  translation_step = 0.1f;
}
