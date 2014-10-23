#include "scene_bonfire.h"

#include <QLabel>
#include <QVBoxLayout>

#include "programs/CG1/opengl/particle_system.h"

SceneBonfire::SceneBonfire(QObject *parent):
  Scene(parent)
{
}

SceneBonfire::~SceneBonfire()
{
}

void SceneBonfire::setup_spec()
{
  QStringList objects = Model::load(":/model/campfire.obj");
  for(int i=0;i<objects.size();i++){
    Object *obj = Object::create(objects[i],objects[i]);
    objects_.push_back(obj);
  }

  ParticleSystem *ps = ParticleSystem::create("Fire Generator", new ParticleBehavior());
  ps->setPosition(QVector3D(0,0.5,0));
  objects_.push_back(ps);

  skybox_ = Object::create("Skydome","skydome");
  skybox_->setOverrideTexture("panoramic_room.jpg");
}

void SceneBonfire::buildControlWidget()
{
  if(control_widget_ == NULL) return;

  control_widget_->setLayout(new QVBoxLayout);
  control_widget_->layout()->addWidget(new QLabel("Bonfire"));
}
