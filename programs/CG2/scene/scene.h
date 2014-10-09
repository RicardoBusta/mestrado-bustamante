#ifndef SCENE_H
#define SCENE_H

#include "sceneobject.h"

//#include <QMatrix4x4>
#include "structures.h"
#include "scenelight.h"

class Scene
{
public:
  Scene();

  QVector<SceneObject> object;
  QVector<SceneObject> transformed_object_;

  SceneObject environment;

  QVector<SceneLight> light;
  QVector<SceneLight> transformed_light;

  QVector<Ric::Vector> frustum;
  QVector<Ric::Vector> transformed_frustum;

  //float modelview_matrix[16];
  //float inverse_modelview_matrix[16];

  //float projection_matrix[16];
  //float inverse_projection_matrix[16];

  Ric::Matrix4x4 pm, ipm;
  Ric::Matrix4x4 vm, ivm;
  Ric::Matrix4x4 pvm, ipvm;
  Ric::Matrix4x4 translate;
  Ric::Matrix4x4 rotate;

  int selected_image_size;

  float rotx, roty, distz;
  float far_plane_z, near_plane_z;
  float fov, ratio;
  int specialx, specialy;

  bool calculate_advanced_light;
  bool track_one_ray;

  bool draw_bounding_box_;

//  bool valid_;

  void calcMatrixes();
  void calcFrustum();

  void loadScene(QString s);
  QVector<SceneObject> findLightObjects(SceneObject &obj);
  void loadDefaultScene1();
  void loadDefaultScene2();
  void loadEnvironmentScene();
  void clearScene();
  void createBox(bool reflect);
  void createWall(bool reflect);
};
#endif // SCENE_H
