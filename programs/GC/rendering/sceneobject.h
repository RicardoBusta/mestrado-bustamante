#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <QVector3D>
#include <QtOpenGL>

class SceneObject
{
public:
  SceneObject(const QString &name, const QString &owner, const int &scale, const QString &color, bool is_algorithm);
  virtual ~SceneObject();

  QString name_;
  QString owner_;
  QColor color_;
  bool visible_;

  bool deleted_;
  double scale_;

  bool is_algorithm_;

  void Draw(const float &spread, const float &shrink, const bool color_per_object, const unsigned int current_frame) const;
  virtual void Colorize()=0;
  virtual void Delete()=0;
  virtual void Vertex(const QVector3D &v) const;
  virtual void Normal(const QVector3D &v) const;
  virtual void Color(const QColor &c) const;

  bool IsAlgorithm();
  virtual void RunAlgorithm();
  virtual bool StepAlgorithm();
protected:
  virtual void DrawObject(const float &spread, const float &shrink, const bool user_color, const unsigned int current_frame) const =0 ;
};

#endif // SCENEOBJECT_H
