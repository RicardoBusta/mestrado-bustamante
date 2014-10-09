#include "particle_behavior.h"

#include "programs/CG1/utils/random.h"
#include "programs/CG1/opengl/particle.h"

const QColor start_color = QColor(0xff,0xff,0x00,0x002);
const QColor end_color = QColor(0xff,0x00,0x00,0x00);
const int life = 100;
const float scale = 0.2f;

QColor color_mult(const QColor &c, const float &f){
  return QColor(c.red()*f,c.green()*f,c.blue()*f);
}

QColor color_sum(const QColor &c1, const QColor &c2){
  return QColor(c1.red()+c2.red(),c1.green()+c2.green(),c1.blue()+c2.blue());
}

ParticleBehavior::ParticleBehavior()
{
}

void ParticleBehavior::initialize(Particle * p)
{
  p->scale_ = scale;
  p->life_ = life;
  p->speed_ = QVector3D(3*(Random::getF()*2.0f-1.0f),Random::getF()*2.0+1.0f,3*(Random::getF()*2.0f-1.0f)).normalized()/20;
  p->color_ = QColor(0xff,0xff,0x00);
  p->texture_ = QString(":/texture/fire_particle_texture.png");
}

void ParticleBehavior::behave(Particle *p)
{
  float p_life = float(p->life_)/float(life);
  p->color_ = color_sum(color_mult(start_color,p_life),color_mult(end_color,(1.0-p_life)));
  p->pos_ += p->speed_;

  QVector3D accel_ = -p->pos_/1000;
  accel_.setY(0);
  p->speed_ = (p->speed_ + accel_);
}
