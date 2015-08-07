#ifndef MODEL_H
#define MODEL_H

#include <QString>
#include <QVector3D>
#include <QVector2D>
#include <QVector>
#include <QMap>

class Vertex{
public:
  Vertex(const QVector3D &position = QVector3D(0,0,0),
         const QVector3D &normal = QVector3D(0,0,1),
         const QVector2D &texcoord = QVector2D(0,0))
    : position_(position),
      normal_(normal),
      texcoord_(texcoord) {}
  QVector3D position() const { return position_; }
  QVector3D normal() const { return normal_; }
  QVector2D texcoord() const { return texcoord_; }
private:
  QVector3D position_;
  QVector3D normal_;
  QVector2D texcoord_;
};

class Model {
public:
  Model();

  void Draw() const;

  static Model Load(QString filename);
  static Model LoadTriangle();
  static Model LoadCube();

  QString name() const { return name_; }

  void ToggleHide(){ hidden_ = !hidden_; }

private:
  QString name_;
  bool hidden_;
  QVector<Vertex> mesh_;
};

typedef QMap<QString,Model> ModelMap;

#endif // MODEL_H
