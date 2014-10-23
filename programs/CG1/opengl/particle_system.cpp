#include "particle_system.h"

#include <QtOpenGL>

ParticleSystem::ParticleSystem()
{
  source_behavior_ = NULL;
  num_particles_generated_ = 10;
}

ParticleSystem *ParticleSystem::create(QString object_name, ParticleBehavior *source_behavior)
{
  ParticleSystem *p = new ParticleSystem();
  p->source_behavior_ = source_behavior;
  p->setName(object_name);
  return p;
}

void ParticleSystem::set_source_behavior(ParticleBehavior *source_behavior)
{
  source_behavior_ = source_behavior;
}

void ParticleSystem::preDraw()
{
  glPushMatrix();
  glTranslatef(position_.x(),position_.y(),position_.z());
  for(int i=0;i<particles_.size();i++){
    particles_[i].preDraw();
  }
  qSort(particles_);
  glPopMatrix();
}

void ParticleSystem::draw() const
{
  for(int i=0;i<particles_.size();i++){
    particles_[i].draw();
  }
}

void ParticleSystem::step()
{
  for(int i=particles_.size()-1; i>=0; i--){
    if(!particles_[i].alive()){
      particles_.removeAt(i);
    }
  }

  if(source_behavior_!=NULL){
    for(int i=0;i<num_particles_generated_;i++){
      particles_.push_back(Particle(source_behavior_));
    }
  }

  for(int i=0;i<particles_.size();i++){
    particles_[i].step();
  }
}
