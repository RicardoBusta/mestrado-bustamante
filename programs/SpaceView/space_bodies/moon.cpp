#include "moon.h"

Moon::Moon():
  Object()
{
  model_name = "Sphere";
  texture = ":/texture/texture_moon.jpg";
  current_translation_angle = 90;
  radius = 0.273;
  draw_orbit = true;
  object_name = "Moon";
}
