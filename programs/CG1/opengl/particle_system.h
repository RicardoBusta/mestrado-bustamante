#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "programs/CG1/opengl/particle.h"
#include "programs/CG1/opengl/particle_behavior.h"
#include "programs/CG1/opengl/object.h"

#include <QList>

class ParticleSystem : public Object
{
public:
  ParticleSystem();

  static ParticleSystem *create(QString object_name, ParticleBehavior *source_behavior);

  ParticleBehavior * source_behavior_;

  void preDraw();
  void draw() const;
  void step();
private:
  QList<Particle> particles_;

  int num_particles_generated_;

//  position_
//  position_variation_

//  speed_
//  speed_variation_
};

#endif // PARTICLESYSTEM_H
