#ifndef SCENE_VOXEL_H
#define SCENE_VOXEL_H

#include "programs/CG1/opengl/scene.h"

#include <QLayout>

class SceneVoxel : public Scene
{
  Q_OBJECT
public:
  explicit SceneVoxel(QObject *parent=0);
  virtual ~SceneVoxel();
private:
  void drawObjects() const;
  void setup_spec();

  QLayout *layout;

  void buildControlWidget();
private slots:
  void setVoxelScene(QString scene);

};

#endif // SCENE_VOXEL_H
