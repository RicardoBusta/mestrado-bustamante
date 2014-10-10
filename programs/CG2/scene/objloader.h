#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <QVector>
#include <QMap>

#include "scene/sceneobject.h"
#include "scene/triangleface.h"
#include "structures/material.h"

class ObjLoader
{
public:
  ObjLoader();

  static SceneObject LoadObj(QString filename, QMap<QString,Ric::Material> *mtl_map);
  static QMap<QString,Ric::Material> LoadMtl(QString filename);

  static void UpdateMaxAndMin(QVector3D &max, QVector3D &min, const Ric::Vector &v);
  static QVector<TriangleFace> CreateBoundingBox(const QVector3D &min, const QVector3D &max);
private:
  static QString ReadValidLine(QTextStream &in);
};

#endif // OBJLOADER_H
