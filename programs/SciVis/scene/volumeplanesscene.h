#ifndef VOLUMEPLANESSCENE_H
#define VOLUMEPLANESSCENE_H

#include "busta_libs/glwidget/glwidgetscene.h"

#include <QString>

class VolumePlanesScene : public Busta::GLWidgetScene
{
public:
  explicit VolumePlanesScene();

  void init();
  void paintGL();
  void release();

  void setTex3D();

  void transferFunction(unsigned short val, unsigned char *ret);

  unsigned int textureID;

  int layers;

  QString file_name;
};

#endif // VOLUMEPLANESSCENE_H
