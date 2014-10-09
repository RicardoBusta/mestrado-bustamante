#include "animation.h"

#include "programs/CG1/opengl/object.h"

Animation::Animation()
{
}

void Animation::step()
{
  step_spec();
}

void Animation::transform()
{
  transform_spec();
}
