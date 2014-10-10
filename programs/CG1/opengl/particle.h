#ifndef PARTICLE_H
#define PARTICLE_H

#include <QVector3D>
#include <QColor>

class ParticleBehavior;

class Particle
{
private:
  friend class ParticleSystem;
  friend class ParticleBehavior;

  QVector3D pos_;
  QVector3D speed_;
  QColor color_;
  float scale_;
  int life_;
  QString texture_;
  ParticleBehavior *pb_;

  float transform[16];

  bool alive();

  void preDraw();
  void draw() const;
  void step();

public:
  Particle(ParticleBehavior *pb);

  bool operator<(const Particle &p) const;
  Particle operator=(const Particle &p);
};

#endif // PARTICLE_H
