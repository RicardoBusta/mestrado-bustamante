#include "scene_obj.h"

#include "ui_obj_widget.h"

#include <QFileDialog>

SceneObj::SceneObj(QObject *parent):
  Scene(parent)
{
}

void SceneObj::buildControlWidget()
{
  Ui::ObjWidget *ui = new Ui::ObjWidget;
  ui->setupUi(control_widget_);

  connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(loadObjFile()));
}

void SceneObj::loadObjFile()
{
  QStringList filenames = QFileDialog::getOpenFileNames(control_widget_,"Open Model File",".");

  for(int i=0;i<objects_.size();i++){
    delete objects_[i];
  }

  objects_.clear();

  for(int i=0;i<filenames.size();i++){
    QStringList objects = Model::load(filenames[i]);

    for(int j=0;j<objects.size();j++){
      Object *obj = Object::create(filenames[i].right(10)+"_"+objects[j],objects[j]);
      objects_.push_back(obj);
    }
  }
}
