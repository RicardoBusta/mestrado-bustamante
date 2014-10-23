#ifndef SCENE_H
#define SCENE_H

#include <QVector>
#include <QObject>

#include "programs/CG1/opengl/object.h"

class Scene : public QObject
{
  Q_OBJECT
public:

  explicit Scene(QObject *parent=0);
  virtual ~Scene();

  void setup();

  // Camera Manipulation
  void addZoom(int zoom);

  void rotate(int rot_x, int rot_y, int rot_z);

  // Init OpenGL
  static void initialize();
  void resize(int w,int h);

  // Paint OpenGL
  void setOptions();
  void clear() const;
  void pre_draw() const;
  void draw() const;
  void post_draw() const;
  void drawArtifacts() const;

  // Scene Animation Manipulation
  void step();

  // Scenes
  static void addScene(QString scene_name,Scene* scene);
  static bool valid();
  static Scene* current();
  static QString current_name();
  static void setCurrent(QString scene_name);
  static QStringList scene_list();

  QStringList getObjectList() const;

  QWidget *controlWidget();

  virtual void applyCameraConstraint();

  float zoom() const;
protected:
  virtual void setup_spec();

  Object *skybox_;
  QVector<Object*> objects_;

  virtual void preDraw() const;
  virtual void postDraw() const;

  virtual void drawSkybox() const;
  virtual void drawObjects() const;

  float rot_x() const;
  float rot_y() const;
  float rot_z() const;

  void GlVertex(const QVector3D &v) const;
  void GlColor(const QColor &c) const;

  virtual void buildControlWidget();
  QWidget *control_widget_;

  float rot_x_;
  float rot_y_;
  float rot_z_;

private:
  void setZoom(float zoom);

  bool initialized_;
  static Scene *instance_;

  float zoom_;

  static QMap<QString,Scene*> scene_;
  static QString current_scene_;
};

#endif // SCENE_H
