#include "venus.h"

Venus::Venus():
  Object()
{
  model_name = "Sphere";
  texture = ":/texture/texture_venus.jpg";
  radius = 10;
  draw_orbit= true;
  object_name = "Venus";
  translation_x_radius = 1000;
  translation_z_radius = 1000;
  translation_step = 0.2f;
}
