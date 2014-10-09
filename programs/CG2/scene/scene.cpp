#include "scene.h"

#include <cmath>
#include <math.h>
#include "constants.h"
#include "triangleface.h"
#include "structures/material.h"

#include "scene/objloader.h"

Scene::Scene()
  : rotx(15),
    roty(0),
    distz(0),
    far_plane_z(kDefaultFar),
    near_plane_z(kDefaultNear),
    fov(kDefaultFov),
    ratio(kDefaultRatio),
    specialx(20),
    specialy(20),
    calculate_advanced_light(false),
    track_one_ray(false),
    draw_bounding_box_(true)
  //    valid_(false)
{
  frustum.resize(9);

  //  loadDefaultScene1();

  loadEnvironmentScene();

  calcFrustum();
}

void Scene::calcMatrixes()
{
  //  if(!valid_) return;
  pm.SetToIdentity();
  vm.SetToIdentity();
  vm.Translate(0,0,-10+distz);
  vm.Rotate(rotx,1,0,0);
  vm.Rotate(roty,0,1,0);
  vm.Scale(0.5);

  pvm = vm;

  //  ipvm.SetToIdentity();
  //  ipvm.Scale(2);
  //  ipvm.Rotate(-roty,0,1,0);
  //  ipvm.Rotate(-rotx,1,0,0);
  //  ipvm.Translate(0,0,10-distz);

  ipvm = pvm.Inverted();

  transformed_object_.clear();
  foreach(SceneObject o, object){
    transformed_object_.push_back(SceneObject(&o,&pvm));
  }
  transformed_light.clear();
  foreach(SceneLight l, light){
    transformed_light.push_back(SceneLight(&l,&pvm));
  }

  transformed_frustum.clear();
  foreach(Ric::Vector v, frustum){
    transformed_frustum.push_back(Ric::Vector(&v,&ipvm));
  }
}

void Scene::calcFrustum()
{
  //  if(!valid_) return;
  float frustum_angle_x_ = (fov)*(M_PI/180.0f);
  float frustum_angle_y_ = (fov*ratio)*(M_PI/180.0f);

  float tx = tan(frustum_angle_x_/2.0f);
  float ty = tan(frustum_angle_y_/2.0f);

  float frustum_near_side_x = near_plane_z * tan(frustum_angle_x_/2.0f);
  float frustum_near_side_y = near_plane_z * tan(frustum_angle_y_/2.0f);
  float frustum_far_side_x = far_plane_z * tan(frustum_angle_x_/2.0f);
  float frustum_far_side_y = far_plane_z * tan(frustum_angle_y_/2.0f);

  //glFrustum(-frustum_side_x,frustum_side_x,-frustum_side_y,frustum_side_y,near_,far_);

  //  frustum.resize(9);
  frustum[0] = Ric::Vector(0,0,0,1);
  frustum[1] = Ric::Vector(-frustum_near_side_x,-frustum_near_side_y,-near_plane_z,1);
  frustum[2] = Ric::Vector( frustum_near_side_x,-frustum_near_side_y,-near_plane_z,1);
  frustum[3] = Ric::Vector( frustum_near_side_x, frustum_near_side_y,-near_plane_z,1);
  frustum[4] = Ric::Vector(-frustum_near_side_x, frustum_near_side_y,-near_plane_z,1);
  frustum[5] = Ric::Vector(-frustum_far_side_x,-frustum_far_side_y,-far_plane_z,1);
  frustum[6] = Ric::Vector( frustum_far_side_x,-frustum_far_side_y,-far_plane_z,1);
  frustum[7] = Ric::Vector( frustum_far_side_x, frustum_far_side_y,-far_plane_z,1);
  frustum[8] = Ric::Vector(-frustum_far_side_x, frustum_far_side_y,-far_plane_z,1);
}

void Scene::loadScene(QString s)
{
  QMap<QString,Ric::Material> material = ObjLoader::LoadMtl("://models/"+s+".mtl");
  object.push_back( ObjLoader::LoadObj("://models/"+s+".obj",&material) );
  //  qDebug() << "one crystal loaded";
  object.push_back(object.last());
  //  object[object.size()-1].move(Ric::Vector(5,0,0));
  //  object[object.size()-2].move(Ric::Vector(-5,0,0));

  //  qDebug() << object.last().child_objects_.size();

  //  createBox(true);
  //  object.last().scale(-14);

  int light_size = 1;
  float light_spread = 0.5;

  QVector<SceneObject> light_objects;



  QVector<SceneObject>::iterator object_it = object.begin();
  for(;object_it!=object.end();object_it++){
    light_objects += findLightObjects( (*object_it) );
  }

  if(light_objects.empty()){
    for(int i=0;i<light_size;i++)
      for(int j=0;j<light_size;j++)
        for(int k=0;k<light_size;k++){
          light.push_back(SceneLight(
                            Ric::Vector(float(i)*light_spread,float(j)*light_spread,float(k)*light_spread)+Ric::Vector(10,10,0),
                            Ric::LightComponent(
                              /*dif*/ Ric::Color(0xffffffff)/(light_size*light_size*light_size),
                              /*spe*/ Ric::Color(0xffffffff)/(light_size*light_size*light_size),
                              /*amb*/ Ric::Color(0xff151515)/(light_size*light_size*light_size)
                              ),
                            30.0
                            ));
        }
  }else{
  QVector<SceneObject>::iterator light_it = light_objects.begin();
  const SceneObject &obj = ((SceneObject)(*light_it));
  for(;light_it!=light_objects.end();light_it++)
    for(int i=0;i<light_size;i++)
      for(int j=0;j<light_size;j++)
        for(int k=0;k<light_size;k++){
          light.push_back(SceneLight(
                            Ric::Vector(float(i)*light_spread,float(j)*light_spread,float(k)*light_spread)+Ric::Vector((*light_it).center_),
                            Ric::LightComponent(
                              /*dif*/ Ric::Color(0xffffffff)/(light_size*light_size*light_size),
                              /*spe*/ Ric::Color(0xffffffff)/(light_size*light_size*light_size),
                              /*amb*/ Ric::Color(0xff151515)/(light_size*light_size*light_size)
                              ),
                            30.0
                            ));
        }
  }
}

QVector<SceneObject> Scene::findLightObjects(SceneObject &obj)
{
  QVector<SceneObject> light_objects;
  QVector<SceneObject>::iterator object_it = obj.child_objects_.begin();
  for(;object_it!=obj.child_objects_.end();object_it++){
    if( (*object_it).material_.isLight() ){
      light_objects.push_back( (*object_it) );
      obj.child_objects_.erase(object_it);
    }else{
      light_objects += findLightObjects(*object_it);
    }
  }
  return light_objects;
}

void Scene::loadDefaultScene1()
{
  createBox(false);
  object.last().scale(3);
  object.last().move(Ric::Vector(7,0,0,0));

  createBox(false);
  object.last().scale(3);
  object.last().move(Ric::Vector(-7,0,0,0));

  createBox(true);
  object.last().scale(-15);

  createWall(true);
  object.last().scale(10);
  object.last().move(Ric::Vector(0,0,-7,0));

  const int light_size = 1;
  const float light_spread = 0.5f;
  for(int i=0;i<light_size;i++)
    for(int j=0;j<light_size;j++)
      for(int k=0;k<light_size;k++){
        light.push_back(SceneLight(
                          Ric::Vector(0+float(i)*light_spread,10+float(j)*light_spread,0+float(k)*light_spread),
                          Ric::LightComponent(
                            /*dif*/ Ric::Color(0xffffffff)/(light_size*light_size*light_size),
                            /*spe*/ Ric::Color(0xffffffff)/(light_size*light_size*light_size),
                            /*amb*/ Ric::Color(0xff151515)/(light_size*light_size*light_size)
                            ),
                          30.0
                          ));
      }
}

void Scene::loadDefaultScene2()
{
  QMap<QString,Ric::Material> material = ObjLoader::LoadMtl("://models/one_crystal.mtl");
  object.push_back( ObjLoader::LoadObj("://models/one_crystal.obj",&material) );
  //  qDebug() << "one crystal loaded";
  object.push_back(object.last());
  object[object.size()-1].move(Ric::Vector(5,0,0));
  object[object.size()-2].move(Ric::Vector(-5,0,0));

  //  qDebug() << object.last().child_objects_.size();

  createBox(true);
  object.last().scale(-15);

  const int light_size = 1;
  const float light_spread = 0.5f;
  for(int i=0;i<light_size;i++)
    for(int j=0;j<light_size;j++)
      for(int k=0;k<light_size;k++){
        light.push_back(SceneLight(
                          Ric::Vector(0+float(i)*light_spread,10+float(j)*light_spread,0+float(k)*light_spread),
                          Ric::LightComponent(
                            /*dif*/ Ric::Color(0xffffffff)/(light_size*light_size*light_size),
                            /*spe*/ Ric::Color(0xffffffff)/(light_size*light_size*light_size),
                            /*amb*/ Ric::Color(0xff151515)/(light_size*light_size*light_size)
                            ),
                          30.0
                          ));
      }
}

void Scene::loadEnvironmentScene()
{
  qDebug() << "load enviro scene";
  QMap<QString,Ric::Material> material = ObjLoader::LoadMtl("://models/environment.mtl");
  environment = ObjLoader::LoadObj("://models/environment.obj",&material);
}

void Scene::clearScene()
{
  object.clear();
  light.clear();
}

static int name_id = 0;

void Scene::createBox(bool reflect)
{
  Ric::Vector p0 = Ric::Vector(-1,-1,1);
  Ric::Vector p1 = Ric::Vector(+1,-1,1);
  Ric::Vector p2 = Ric::Vector(+1,+1,1);
  Ric::Vector p3 = Ric::Vector(-1,+1,1);

  Ric::Vector p4 = Ric::Vector(-1,-1,-1);
  Ric::Vector p5 = Ric::Vector(+1,-1,-1);
  Ric::Vector p6 = Ric::Vector(+1,+1,-1);
  Ric::Vector p7 = Ric::Vector(-1,+1,-1);

  object.push_back(SceneObject());


  object.last().name = QString("Box%1").arg(name_id++);

  object.last().faces_.push_back(TriangleFace(p0,p1,p2,Ric::Material::Create(0xff800000)));
  object.last().faces_.push_back(TriangleFace(p0,p2,p3,Ric::Material::Create(0xffff0101)));

  object.last().faces_.push_back(TriangleFace(p4,p6,p5,Ric::Material::Create(0xff808000)));
  object.last().faces_.push_back(TriangleFace(p4,p7,p6,Ric::Material::Create(0xffffff00)));

  object.last().faces_.push_back(TriangleFace(p0,p3,p7,Ric::Material::Create(0xff008000)));
  object.last().faces_.push_back(TriangleFace(p0,p7,p4,Ric::Material::Create(0xff00ff00)));

  object.last().faces_.push_back(TriangleFace(p1,p5,p6,Ric::Material::Create(0xff008080)));
  object.last().faces_.push_back(TriangleFace(p1,p6,p2,Ric::Material::Create(0xff00ffff)));

  object.last().faces_.push_back(TriangleFace(p1,p0,p4,Ric::Material::Create(0xff000080)));
  object.last().faces_.push_back(TriangleFace(p1,p4,p5,Ric::Material::Create(0xff0000ff)));

  object.last().faces_.push_back(TriangleFace(p3,p2,p6,Ric::Material::Create(0xff800080)));
  object.last().faces_.push_back(TriangleFace(p3,p6,p7,Ric::Material::Create(0xffff00ff)));
}

void Scene::createWall(bool reflect)
{
  Ric::Vector p0 = Ric::Vector(-1,-1,0);
  Ric::Vector p1 = Ric::Vector(+1,-1,0);
  Ric::Vector p2 = Ric::Vector(+1,+1,0);
  Ric::Vector p3 = Ric::Vector(-1,+1,0);

  object.push_back(SceneObject());
  object.last().name = QString("Wall%1").arg(name_id++);

  object.last().faces_.push_back(TriangleFace(p0,p1,p2,Ric::Material::CreateWithReflection(0xffffffff,1.0)));
  object.last().material_.SetReflection(0.4);
  object.last().faces_.push_back(TriangleFace(p0,p2,p3,Ric::Material::CreateWithReflection(0xffffffff,1.0)));
  object.last().material_.SetReflection(0.4);

  object.last().faces_.push_back(TriangleFace(p0,p2,p1,Ric::Material::CreateWithReflection(0xffffffff,1.0)));
  object.last().material_.SetReflection(0.4);
  object.last().faces_.push_back(TriangleFace(p0,p3,p2,Ric::Material::CreateWithReflection(0xffffffff,1.0)));
  object.last().material_.SetReflection(0.4);
}
