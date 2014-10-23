#include "object.h"

#include <QFile>
#include <QDebug>
#include <QStringList>
#include <QtOpenGL>

#include "programs/CG1/utils/options.h"
#include "programs/CG1/opengl/textures.h"
#include "programs/CG1/utils/common.h"
#include "programs/CG1/opengl/animation.h"

Object::Object():
  valid_(false),
  scale_(1.0f),
  visible_(true),
  has_custom_color_(false),
  model_(NULL)
{
}

Object::~Object()
{
  for(QList<Animation*>::iterator it = animation_.begin(); it!=animation_.end(); it++){
    if((*it)!=NULL){
      delete (*it);
      (*it)= NULL;
    }
  }
}

Object *Object::create(QString object_name, QString model_name)
{
  Object *o = new Object();

  o->name_ = object_name;
  o->setModel(model_name);

  return o;
}

void Object::setModel(QString model_name)
{
  model_ = Model::get(model_name);
}

void Object::preDraw()
{
}

void Object::draw() const
{
  if(model_==NULL) return;
  if(visible_==false) return;

  glPushMatrix();

  if(has_custom_color_){
    glColor4f(custom_color_.redF(),custom_color_.greenF(),custom_color_.blueF(),custom_color_.alphaF());
  }else{
    model_->setMaterial();
  }

  if(Options::instance()->get_option("check_alt_texture") && alt_texture_!=""){
    Textures::instance()->setTexture(alt_texture_);
  }
  else if(override_texture_!=""){
    Textures::instance()->setTexture(override_texture_);
  }else{
    model_->setTexture();
  }

  transform();

  model_->draw();

  glPopMatrix();
}

void Object::drawArtifacts() const
{
  if(model_==NULL) return;
  if(visible_==false) return;

  glPushMatrix();

  transform();

  model_->drawArtifacts();

  glPopMatrix();
}

void Object::transform() const
{
  glTranslatef(position_.x(),position_.y(),position_.z());

  glRotatef(euler_rotation_.x(),1,0,0);
  glRotatef(euler_rotation_.y(),0,1,0);
  glRotatef(euler_rotation_.z(),0,0,1);

  glScalef(scale_,scale_,scale_);

  for(QList<Animation*>::const_iterator it = animation_.begin(); it!=animation_.end(); it++){
    if((*it)!=NULL)
      (*it)->transform();
  }

}

void Object::step()
{
  for(QList<Animation*>::iterator it = animation_.begin(); it!=animation_.end(); it++){
    if((*it)!=NULL)
      (*it)->step();
  }
}

void Object::setEulerRotation(float x, float y, float z)
{
  euler_rotation_ = QVector3D(x,y,z);
}

void Object::setEulerRotation(QVector3D rot)
{
  euler_rotation_ = rot;
}

void Object::setPosition(QVector3D pos)
{
  position_ = pos;
}

void Object::setScale(float s)
{
  scale_ = s;
}

void Object::setCustomColor(QColor c)
{
  has_custom_color_ = true;
  custom_color_ = c;
}

void Object::setAltTexture(QString a)
{
  alt_texture_ = a;
}

void Object::setOverrideTexture(QString s)
{
  override_texture_ = s;
}

void Object::setVisible(bool visible)
{
  visible_ = visible;
}

Object Object::operator=(Object o)
{
  name_ = o.name_;
  valid_ = o.valid_;
  material_ = o.material_;

  override_texture_ = o.override_texture_;

  position_ = o.position_;
  euler_rotation_ = o.euler_rotation_;

  model_ = o.model_;

  return *this;
}

QString Object::name() const
{
  return name_;
}

void Object::setName(QString name)
{
  name_ = name;
}

void Object::addAnimation(Animation *animation)
{
  if(animation!=NULL){
    animation_.push_back(animation);
  }
}
