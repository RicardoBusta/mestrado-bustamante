#ifndef SCENETETRADELAUNAY_H
#define SCENETETRADELAUNAY_H

#include "rendering/sceneobject.h"
#include "rendering/qhpoly.h"
#include "rendering/deltetra.h"

class SceneTetraDelaunay : public SceneObject
{
public:
  SceneTetraDelaunay(const QString &name, const QString &owner, const double &spread, const QString &color);
  ~SceneTetraDelaunay();

  void DrawObject(const float &spread, const float &shrink, const bool user_color, const unsigned int current_frame) const;
  void Clear();
  void Colorize();
  void Delete();

  void RunAlgorithm();

  bool StepAlgorithm();
  int step_count_;

  QVector<QVector3D> points_;

  // Algorithm step structures
  QVector<QVector3D> marked_points_;

  //first face
  QVector<int> v_max;
  QVector<int> v_3_sel;
  QVector<QHPoly> todo_poly_list;
  QVector<int> horizon_ridge_faces;
  QVector<int> horizon_ridge;
  int max_dist_vert;
  QVector<bool> points_valid_;
  QVector<QHPoly> poly_;
  bool FindFirstFace();

  //tetra
  QVector<DelTetra> tetra_;
//  QVector<bool> dead_points_;

  double OrientedSolidAngle(const QVector3D &p, const QHPoly &face);

  bool Intersection(const QHPoly &poly, const QVector3D &v1, const QVector3D &v2);
  bool Intersection(const QHPoly &poly, const QHPoly &face);
  bool Intersection(const QHPoly &poly, const DelTetra &tetra);

  float DistanceSquaredBetweenPoints(const QVector3D &p1, const QVector3D &p2) const;
};

#endif // SCENETETRADELAUNAY_H
