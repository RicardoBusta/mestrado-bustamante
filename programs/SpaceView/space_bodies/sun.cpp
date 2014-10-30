#include "sun.h"

Sun::Sun():
  Object()
{
  model_name = "Sphere";
  texture = ":/texture/texture_sun.jpg";
  orbit = false;
  emit_light = true;
  object_name = "Sun";
  tilt = 0;
  radius = 109;
}
