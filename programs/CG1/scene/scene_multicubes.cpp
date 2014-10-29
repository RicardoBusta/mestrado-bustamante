#include "scene_multicubes.h"

SceneMultiCubes::SceneMultiCubes(QObject *parent):
  Scene(parent)
{
}

void SceneMultiCubes::setup_spec()
{
  Model::load(":/model/multicube.obj");
  Model::load(":/model/skydome.obj");

  Object *box = Object::create("MultiCubes","multicube");
  objects_.push_back(box);

  skybox_ = Object::create("Skydome","skydome");
  skybox_->setOverrideTexture("clearskydome.jpg");
}

void SceneMultiCubes::buildControlWidget()
{

}
