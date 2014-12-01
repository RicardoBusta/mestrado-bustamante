#ifndef VOLUMEPLANESSCENE_H
#define VOLUMEPLANESSCENE_H

#include "busta_libs/glwidget/glwidgetscene.h"

#include <QtOpenGL>
#include <QString>
#include "algorithm/transferfunction.h"

class VolumePlanesScene : public Busta::GLWidgetScene
{
public:
  explicit VolumePlanesScene();

  void init();
  void paintGL();
  void release();

  void setList();
  void setTex3D();

  void transferFunction(unsigned short val, GLubyte *ret);

  unsigned int textureID;

  int layers;

  GLuint display_list;
  TransferFunction tf;

  QString file_name;
};

#endif // VOLUMEPLANESSCENE_H
