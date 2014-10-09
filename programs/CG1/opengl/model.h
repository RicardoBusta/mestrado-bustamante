#ifndef MODEL_H
#define MODEL_H

#include <QDebug>
#include <QString>
#include <QVector>
#include <QVector2D>
#include <QVector3D>

class Model
{
public:
  Model();

  static QStringList load(QString file_name);

  void setMaterial();
  void setTexture();
  void draw() const;
  void drawArtifacts() const;

  static Model* get(QString model_name);

  static QStringList getList();

private:
  struct Face{
    QVector3D v[3];
    QVector3D n[3];
    QVector2D t[3];

    Face operator=(Face f){
      for(int i=0;i<3;i++){
        v[i] = f.v[i];
        n[i] = f.n[i];
        t[i] = f.t[i];
      }
      return *this;
    }
  };

  bool valid_;
  QString material_;

  static QMap<QString,Model*> model_;

  QVector<struct Face> face_;
};

#endif // MODEL_H
