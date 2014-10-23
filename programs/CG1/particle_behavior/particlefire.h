#ifndef PARTICLEFIRE_H
#define PARTICLEFIRE_H

#include "opengl/particle_behavior.h"

class ParticleFire : public ParticleBehavior
{
public:
  ParticleFire();

  virtual void initialize(Particle *p);
  virtual void behave(Particle *p);
};

#endif // PARTICLEFIRE_H
