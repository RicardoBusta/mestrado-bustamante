#include "scene_donut.h"

SceneDonut::SceneDonut(QObject *parent):
  Scene(parent)
{
}

SceneDonut::~SceneDonut()
{
}

void SceneDonut::setup_spec()
{
  Model::load(":/model/donut.obj");
  Model::load(":/model/skydome.obj");

  Object *box = Object::create("Donut Box","box");
  objects_.push_back(box);

  Object *d1 = Object::create("Donut","donut");
  Object *d1_c = Object::create("Donut Cover","donut_cover");
  Object *d1_t = Object::create("Donut Top","donut_top");

  objects_.push_back(d1);
  objects_.push_back(d1_c);
  objects_.push_back(d1_t);

  Object *d2 = Object::create("Choco Donut","choco_donut");
  Object *d2_c = Object::create("Choco Donut Cover","choco_donut_cover");
  Object *d2_t = Object::create("Choco Donut Top","choco_donut_top");

  objects_.push_back(d2);
  objects_.push_back(d2_c);
  objects_.push_back(d2_t);

  skybox_ = Object::create("Skydome","skydome");
  skybox_->setOverrideTexture("panoramic_room.jpg");
}

void SceneDonut::buildControlWidget()
{

}
