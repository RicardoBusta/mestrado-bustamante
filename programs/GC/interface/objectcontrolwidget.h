#ifndef OBJECTCONTROLWIDGET_H
#define OBJECTCONTROLWIDGET_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class ObjectControlWidget;
}

class SceneObject;
class Scene;

class ObjectControlWidget : public QWidget
{
  Q_OBJECT

public:
  explicit ObjectControlWidget(Scene *scene, SceneObject *object, QWidget *parent = 0);
  ~ObjectControlWidget();

  SceneObject *object_;
  Scene *scene_;
private:
  Ui::ObjectControlWidget *ui_;

private slots:
  void ToggleVisible(bool value);
  void DeleteObject();
  void SelectColor();
  void CreateHullObject();
  void CreateTetraObject();
signals:
  void VisibilityChanged();
  void ObjectDeleted();
};

#endif // OBJECTCONTROLWIDGET_H
