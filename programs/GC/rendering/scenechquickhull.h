#ifndef SCENECHQUICKHULL_H
#define SCENECHQUICKHULL_H

#include "rendering/sceneobject.h"

#include "qhpoly.h"

class SceneCHQuickHull: public SceneObject
{
public:
  SceneCHQuickHull(const QString &name, const QString &owner, const double &spread, const QString &color);
  ~SceneCHQuickHull();

  QVector<QVector3D> points_;
  QVector<bool> points_valid_;
  QVector<QHPoly> poly_;

//  QVector<QHPoly> t_list;

//  QVector<int> v_s;

  void DrawObject(const float &spread, const float &shrink, const bool user_color, const unsigned int current_frame) const;
  void Clear();
  void Colorize();
  void Delete();

  void RunAlgorithm();

  bool StepAlgorithm();
  int step_count_;

  QVector<int> v_max;
  QVector<int> v_3_sel;
  QVector<QHPoly> todo_poly_list;
  QVector<int> horizon_ridge_faces;
  QVector<int> horizon_ridge;
//  QVector<int> horizon_not_ridge;
  int max_dist_vert;

  float DistanceSquaredBetweenPoints(const QVector3D &p1, const QVector3D &p2) const;
};

#endif // SCENECHQUICKHULL_H
