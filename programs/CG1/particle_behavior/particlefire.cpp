#include "particlefire.h"

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


ParticleFire::ParticleFire()
{
}

void ParticleFire::initialize(Particle *p)
{
  p->set_scale( scale );
  p->set_life( life );
  p->set_speed( QVector3D(3*(Random::getF()*2.0f-1.0f),Random::getF()*2.0+1.0f,3*(Random::getF()*2.0f-1.0f)).normalized()/20 );
  p->set_color( QColor(0xff,0xff,0x00) );
  p->set_texture ( QString(":/texture/fire_particle_texture.png") );
}

void ParticleFire::behave(Particle *p)
{
  float p_life = float(p->life())/float(life);
  p->set_color( color_sum(color_mult(start_color,p_life),color_mult(end_color,(1.0-p_life))) );
  p->set_pos( p->pos()+p->speed() );

  //if(Random::getF() > 0.8) return;

  QVector3D accel_ = -p->pos()/1000.0f;

  if(Random::getF() > 0.9) accel_ = -accel_;

  accel_.setY(0);
  p->set_speed( (p->speed() + accel_) );
}
