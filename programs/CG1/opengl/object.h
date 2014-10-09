#ifndef OBJECT_H
#define OBJECT_H

#include <QString>
#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <QColor>

#include "model.h"

class Animation;

class Object
{
public:
  Object();
  ~Object();

  static Object *create(QString object_name,QString model_name);

  void setModel(QString model_name);

  virtual void preDraw();
  virtual void draw() const;
  virtual void drawArtifacts() const;

  virtual void step();

  void setEulerRotation(float x, float y, float z);
  void setEulerRotation(QVector3D rot);
  void setPosition(QVector3D pos);
  void setScale(float s);
  void setCustomColor(QColor c);
  void setAltTexture(QString a);

  void setOverrideTexture(QString s);

  void setVisible(bool visible);

  Object operator=(Object o);

  QString name() const;
  void setName(QString name);

  void addAnimation(Animation *animation);
protected:
  void transform() const;

  QString name_;

  bool valid_;
  QString material_;

  bool visible_;

  QString override_texture_;

  QString alt_texture_;

  QVector3D position_;
  QVector3D euler_rotation_;
  float scale_;

  bool has_custom_color_;
  QColor custom_color_;

  Model *model_;

  QList<Animation*> animation_;
};

#endif // OBJECT_H
