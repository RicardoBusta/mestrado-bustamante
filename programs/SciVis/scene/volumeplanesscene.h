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

  void setTex3D();

  unsigned short transferFunction(unsigned short val);

  unsigned int textureID;
};

#endif // VOLUMEPLANESSCENE_H
