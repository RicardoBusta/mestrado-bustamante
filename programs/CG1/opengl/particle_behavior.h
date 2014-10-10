#ifndef PARTICLE_BEHAVIOR_H
#define PARTICLE_BEHAVIOR_H

class Particle;

class ParticleBehavior
{
public:
  ParticleBehavior();
private:
  friend class Particle;

  virtual void initialize(Particle *p);
  virtual void behave(Particle *p);
};

#endif // PARTICLEBEHAVIOR_H
