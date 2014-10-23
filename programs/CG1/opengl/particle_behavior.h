#ifndef PARTICLE_BEHAVIOR_H
#define PARTICLE_BEHAVIOR_H

class Particle;

class ParticleBehavior
{
public:
  ParticleBehavior();

  virtual void initialize(Particle *p)=0;
  virtual void behave(Particle *p)=0;
};

#endif // PARTICLEBEHAVIOR_H
