#include "particle.h"

#include <QtOpenGL>
#include "programs/CG1/opengl/scene.h"
#include "programs/CG1/opengl/textures.h"
#include "programs/CG1/opengl/particle_behavior.h"

Particle::Particle(ParticleBehavior * pb)
{
  pb_ = pb;
  pb_->initialize(this);
}

bool Particle::alive()
{
  if(life_>0){
    return true;
  }
  return false;
}

void Particle::preDraw()
{
  glPushMatrix();
  glTranslatef(pos_.x(),pos_.y(),pos_.z());
  glGetFloatv(GL_MODELVIEW_MATRIX,transform);
  transform[0]=transform[5]=transform[10]=scale_*Scene::current()->zoom();
  transform[1]=transform[2]=transform[4]=transform[6]=transform[8]=transform[9]=0.0;
  glPopMatrix();
}

void Particle::draw() const
{
  Textures::instance()->setTexture(texture_);

  glPushMatrix();

  glLoadMatrixf(transform);

  glNormal3f(0,0,1);
  glColor4f(color_.redF(),color_.greenF(),color_.blueF(),color_.alphaF());

  glBegin(GL_QUADS);
  glTexCoord2f(0,0);
  glVertex3f(-1,-1,0);
  glTexCoord2f(1,0);
  glVertex3f(+1,-1,0);
  glTexCoord2f(1,1);
  glVertex3f(+1,+1,0);
  glTexCoord2f(0,1);
  glVertex3f(-1,+1,0);
  glEnd();
  glPopMatrix();
}

void Particle::step()
{
  pb_->behave(this);
  life_--;
}

bool Particle::operator<(const Particle &p) const{
  return (this->transform[14]<p.transform[14]);
}

Particle Particle::operator=(const Particle &p)
{
  pos_ = p.pos_;
  speed_ = p.speed_;
  color_ = p.color_;
  life_ = p.life_;
  texture_ = p.texture_;
  pb_ = p.pb_;
  scale_ = p.scale_;
  memcpy(transform,p.transform,sizeof(transform));
  return *this;
}
