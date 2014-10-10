#ifndef MATERIAL_H
#define MATERIAL_H

#include <QString>
#include <QMap>
#include <QVector3D>

class Material
{
public:
  Material();

  static void load(QString file_name);

  enum MaterialColor{
    red,
    green,
    blue,
    white,
    black
  };

  void apply_material() const;
  void apply_texture() const;

  static Material *get(QString mtl_name);

    static QStringList getList();
private:
  bool invalid_;

  QString name_;

  QString texture_;

  QVector3D ambient_;
  QVector3D diffuse_;
  QVector3D specular_;
  float shininess_;
  float transparency_;
  int illum_;

  static QMap<QString,Material> material_;
};

#endif // MATERIAL_H
