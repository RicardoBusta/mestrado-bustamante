#ifndef ANIMATIONSPIN_H
#define ANIMATIONSPIN_H

#include "programs/CG1/opengl/animation.h"

#include <QVector3D>

class AnimationSpin : public Animation
{
public:
  enum SPIN_DIRECTION{SPIN_X, SPIN_Y,SPIN_Z, SPIN_AXIS};

  AnimationSpin(float initial_value, float value, SPIN_DIRECTION direction);
  AnimationSpin(float initial_value, float value, QVector3D axis);

private:
  float spin_value_;
  float current_spin_;
  SPIN_DIRECTION spin_direction_;
  QVector3D axis_;

  void step_spec();
  void transform_spec();
};

#endif // ANIMATIONSPIN_H
