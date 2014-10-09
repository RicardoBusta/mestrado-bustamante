#include "animation_spin.h"

#include <QtOpenGL>
#include <QDebug>

AnimationSpin::AnimationSpin(float initial_value, float value, SPIN_DIRECTION direction):
  Animation(),
  current_spin_(initial_value),
  spin_value_(value),
  spin_direction_(direction)
{
  if(direction==SPIN_AXIS){
    axis_ = QVector3D(1,0,0);
  }
}

AnimationSpin::AnimationSpin(float initial_value, float value, QVector3D axis):
  current_spin_(initial_value),
  spin_value_(value),
  spin_direction_(SPIN_AXIS),
  axis_(axis)
{

}

void AnimationSpin::step_spec()
{
  current_spin_ += spin_value_;
}

void AnimationSpin::transform_spec()
{
  switch(spin_direction_){
  case SPIN_X:
    glRotatef(current_spin_,1,0,0);
    break;
  case SPIN_Y:
    glRotatef(current_spin_,0,1,0);
    break;
  case SPIN_Z:
    glRotatef(current_spin_,0,0,1);
    break;
  case SPIN_AXIS:
    glRotatef(current_spin_,axis_.x(),axis_.y(),axis_.z());
    break;
  default:
    break;
  }
}
