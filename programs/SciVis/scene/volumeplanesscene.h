#ifndef VOLUMEPLANESSCENE_H
#define VOLUMEPLANESSCENE_H

#include "busta_libs/glwidget/glwidgetscene.h"
#include "data/volumedata.h"

class VolumePlanesScene : public Busta::GLWidgetScene
{
public:
  explicit VolumePlanesScene();

  void init();
  void paintGL();
  void release();

  VolumeData data;
  QVector<QVector3D> vertex;
};

#endif // VOLUMEPLANESSCENE_H
