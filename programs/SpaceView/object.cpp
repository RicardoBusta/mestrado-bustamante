#include "object.h"

#include "opengl/textures.h"
#include "opengl/model.h"

#include <cmath>

Object::Object()
{
  current_rotation_angle = 0;
  rotation_angle_step = 1;
  current_translation_angle=0;
  translation_step = 1;
  tilt = -15;
  orbit_center = NULL;
  translation_x_radius = 3;
  translation_z_radius = 2;
  orbit = true;
  radius = 1;
  draw_orbit = false;
  emit_light = false;
}

void Object::draw()
{
  glPushMatrix();
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  if(emit_light){
    glDisable(GL_LIGHTING);
  }

  Textures::instance()->setTexture(texture);
  Model *model = Model::get(model_name);

  // Position on orbit
  glTranslatef(pos.x(),pos.y(),pos.z());

  // Body Rotation
  glRotatef(tilt,0,0,1);
  glRotatef(current_rotation_angle,0,1,0);

  // Resize
  glScalef(radius,radius,radius);

  if(model != NULL){
    model->draw();
  }
  glPopAttrib();
  glPopMatrix();
}

void Object::drawOrbit()
{
  if(!draw_orbit) return;

  glBegin(GL_LINE_LOOP);
  QVector3D center;
  if(orbit_center!=NULL){
    center = orbit_center->pos;
  }
  for(int i=0;i<360;i+=10){
    float angle = i*M_PI/180.0f;
    float s = sin(angle);
    float c = cos(angle);

    QVector3D v = center+QVector3D(s*translation_x_radius,0,c*translation_z_radius);
    glVertex3f(v.x(),v.y(),v.z());
  }
  glEnd();
}

void Object::step()
{
  current_rotation_angle += rotation_angle_step;
  current_translation_angle += translation_step;

  // Translation
  if(orbit){
    if(orbit_center!=NULL){
      pos = orbit_center->pos;
    }else{
      pos = QVector3D(0,0,0);
    }
    float angle = current_translation_angle*M_PI/180.0f;
    float s = sin(angle);
    float c = cos(angle);
    QVector3D relative_pos = QVector3D(s*translation_x_radius,0,c*translation_z_radius);
    pos += relative_pos;
  }else{
    pos = QVector3D(0,0,0);
  }
}
