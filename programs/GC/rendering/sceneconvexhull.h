#ifndef SCENECONVEXHULL_H
#define SCENECONVEXHULL_H

#include "rendering/sceneobject.h"

class QhFace;

class SceneConvexHull : public SceneObject
{
public:
  SceneConvexHull(const QString &name, const QString &owner, const double &spread, const QString &color);
  ~SceneConvexHull();

  QVector< QVector<QhFace*> > faces_;

  void DrawObject(const float &spread, const float &shrink, const bool user_color, const unsigned int current_frame) const;
  void ClearFaces();
  void Colorize();
  void Delete();
};

#endif // SCENECONVEXHULL_H
