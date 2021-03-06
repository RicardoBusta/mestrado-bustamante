#ifndef MARCHINGCUBESSCENE_H
#define MARCHINGCUBESSCENE_H

#include "busta_libs/glwidget/glwidgetscene.h"
#include "data/volumedata.h"

class MarchingCubesScene : public Busta::GLWidgetScene
{
public:
  MarchingCubesScene();

  void init();
  void paintGL();
  void release();

  QString file_name;
  int iso_value;
  int cube_size;
  QColor color;
  GLuint display_list;
};

#endif // MARCHINGCUBESSCENE_H
