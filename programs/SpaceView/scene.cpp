#include "scene.h"

#include <QtOpenGL>

#include "opengl/model.h"
#include "opengl/textures.h"

#include "space_bodies/solarsystem.h"
#include "space_bodies/sun.h"
#include "space_bodies/earth.h"
#include "space_bodies/moon.h"
#include "space_bodies/mercury.h"
#include "space_bodies/venus.h"
#include "space_bodies/mars.h"
#include "space_bodies/jupiter.h"
#include "space_bodies/saturn.h"
#include "space_bodies/uranus.h"
#include "space_bodies/neptune.h"
#include "space_bodies/pluto.h"

Scene::Scene()
{
  camera_object = NULL;
  light_object = NULL;
  current_page = 0;
}

float easeineaseout(float x, float slope){
  if(x>1.0) return 1.0;
  if(x<0.0) return 0.0;

  float xs = pow(x,slope);
  float x1s = pow(1-x,slope);

  return xs / (xs + x1s);
}

void Scene::init()
{
  QStringList models;
  models.append(Model::load(":/model/sphere.obj"));
  models.append(Model::load(":/model/dome.obj"));
  qDebug() << models.size()<<"models loaded:" << models;

  Object *space_dome = new Object();
  space_dome->model_name = "Dome";
  space_dome->orbit = false;
  space_dome->radius = 10000;
  space_dome->rotation_angle_step = 0;
  space_dome->texture = ":/texture/texture_space_1.jpg";

  Object *solar_system = new SolarSystem();
  Object *sun = new Sun();
  sun->orbit_center = solar_system;
  Object *earth = new Earth();
  earth->orbit_center = sun;
  Object *moon = new Moon();
  moon->orbit_center = earth;

  Object *mercury = new Mercury();
  mercury->orbit_center = sun;
  Object *venus = new Venus();
  venus->orbit_center = sun;
  Object *mars = new Mars();
  mars->orbit_center = sun;
  Object *jupiter = new Jupiter();
  jupiter->orbit_center = sun;
  Object *saturn = new Saturn();
  saturn->orbit_center = sun;
  Object *neptune = new Neptune();
  neptune->orbit_center = sun;
  Object *uranus = new Uranus();
  uranus->orbit_center = sun;
  Object *pluto = new Pluto();
  pluto->orbit_center = sun;

  light_object = sun;

  camera_object = earth;

  objects.push_back(space_dome);
  objects.push_back(sun);
  objects.push_back(earth);
  objects.push_back(moon);
  objects.push_back(mercury);
  objects.push_back(venus);
  objects.push_back(mars);
  objects.push_back(jupiter);
  objects.push_back(saturn);
  objects.push_back(neptune);
  objects.push_back(uranus);
  objects.push_back(pluto);

  focus.push_back( new SlidePage(sun) );
  focus.push_back( new SlidePage(earth) );
  focus.push_back( new SlidePage(moon) );
  focus.push_back( new SlidePage(mercury) );
  focus.push_back( new SlidePage(venus) );
  focus.push_back( new SlidePage(mars) );
  focus.push_back( new SlidePage(jupiter) );
  focus.push_back( new SlidePage(saturn) );
  focus.push_back( new SlidePage(uranus) );
  focus.push_back( new SlidePage(neptune) );
  focus.push_back( new SlidePage(pluto) );
  focus.push_back( new SlidePage(solar_system) );
  focus.last()->draw_orbit = true;
}

void Scene::draw()
{
  glTranslatef(camera_position.x(),camera_position.y(),camera_position.z());

  if(light_object!=NULL){
    float lpos[] = {light_object->pos.x(),light_object->pos.y(),light_object->pos.z()};
    glLightfv(GL_LIGHT0,GL_POSITION,lpos);
  }

  for(int i=0;i<objects.size();i++){
    objects[i]->draw();

    if(draw_orbit){
      glPushAttrib(GL_ALL_ATTRIB_BITS);
      glDisable(GL_TEXTURE_2D);
      glDisable(GL_LIGHTING);
      objects[i]->drawOrbit();
      glPopAttrib();
    }
  }
}

void Scene::step()
{
  for(int i=0;i<objects.size();i++){
    objects[i]->step();
  }

  if(current_page > focus.size()-1){
    current_page = focus.size()-1;
  }else if(current_page < 0){
    current_page = 0;
  }

  if(focus.size()>0){
    camera_object = focus[current_page]->focus_object;
    draw_orbit = focus[current_page]->draw_orbit;
  }

  if(camera_object!=NULL){
    QVector3D camera_target = -camera_object->pos;

    if(camera_timer >= 1.0){
      camera_position = camera_target;
    }else{

      QVector3D camera_direction = camera_target-camera_position;
      float ct = easeineaseout(camera_timer,2);

      qDebug() << "camera timer" << camera_timer << ct;
      camera_position = ct * camera_target + (1-ct) * camera_position;
      camera_timer+=0.01f;

      float target_zoom = 6*camera_object->radius;
      zoom = ct * target_zoom + (1-ct) * zoom;
    }
  }
}
