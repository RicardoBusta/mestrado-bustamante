#include "objectcontrolwidget.h"
#include "ui_objectcontrolwidget.h"

#include "rendering/sceneobject.h"
#include "rendering/scenepointcloud.h"
#include "rendering/scene.h"

const QString kStringColorButtonStyle = "QPushButton{\n	background-color: %1;\n  border: 1px solid #999;\n	font: bold;\n color: %2;}\n\nQPushButton::hover{\n	border: 1px solid white;\n}";

ObjectControlWidget::ObjectControlWidget(Scene *scene, SceneObject *object, QWidget *parent)
  : QWidget(parent),
    ui_(new Ui::ObjectControlWidget),
    object_(object),
    scene_(scene)
{
  ui_->setupUi(this);

  connect(ui_->delete_button,SIGNAL(clicked()),this,SLOT(DeleteObject()));
  if( NULL == object ){
    ui_->name_label->setText("ERROR");
  }
  ui_->name_label->setText(object_->name_);
  QColor c2 = object_->color_.lightnessF()>0.5?QColor(0,0,0):QColor(255,255,255);
  ui_->color_button->setStyleSheet(kStringColorButtonStyle.arg(object_->color_.name()).arg(c2.name()));
  connect(ui_->visible_check,SIGNAL(toggled(bool)),this,SLOT(ToggleVisible(bool)));
  connect(ui_->color_button,SIGNAL(clicked()),this,SLOT(SelectColor()));

  ScenePointCloud *spc = dynamic_cast<ScenePointCloud*>(object);
  if(NULL == spc){
    ui_->hull_button->hide();
    ui_->simplex_button->hide();
  }else{
    connect(ui_->hull_button,SIGNAL(clicked()),this,SLOT(CreateHullObject()));
    connect(ui_->simplex_button,SIGNAL(clicked()),this,SLOT(CreateTetraObject()));
  }
}

ObjectControlWidget::~ObjectControlWidget()
{
  delete ui_;
}

void ObjectControlWidget::ToggleVisible(bool value)
{
  if( NULL != object_ ){
    object_->visible_ = value;
  }
  emit VisibilityChanged();
}

void ObjectControlWidget::DeleteObject()
{
  if(NULL != object_){
    object_->Delete();
  }
  emit ObjectDeleted();
}

void ObjectControlWidget::SelectColor()
{
  QColor c = QColorDialog::getColor(object_->color_,NULL,"Select "+object_->name_+" Color");
  if(c.isValid()){
    object_->color_ = c;
    QColor c2 = c.lightnessF()>0.5?QColor(0,0,0):QColor(255,255,255);
    ui_->color_button->setStyleSheet(kStringColorButtonStyle.arg(object_->color_.name()).arg(c2.name()));
    emit VisibilityChanged();
  }
}

void ObjectControlWidget::CreateHullObject()
{
  if( NULL != scene_ && NULL != object_ ){
    scene_->StartNewHullAlgorithm(object_);
  }
}

void ObjectControlWidget::CreateTetraObject()
{
  if( NULL != scene_ && NULL != object_ ){
    scene_->StartNewTetraAlgorithm(object_);
  }
}
