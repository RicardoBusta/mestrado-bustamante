#ifndef VOLUMEPLANESSCENE_H
#define VOLUMEPLANESSCENE_H

#include "busta_libs/glwidget/glwidgetscene.h"


class VolumePlanesScene : public Busta::GLWidgetScene
{
public:
  explicit VolumePlanesScene();

  void init();
  void paintGL();
  void release();

  unsigned int textureID;
};

#endif // VOLUMEPLANESSCENE_H
