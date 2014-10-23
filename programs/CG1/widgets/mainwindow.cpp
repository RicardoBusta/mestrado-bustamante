#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "programs/CG1/opengl/material.h"
#include "programs/CG1/opengl/textures.h"
#include "programs/CG1/scene/scene_pie.h"
#include "programs/CG1/scene/scene_tire.h"
#include "programs/CG1/scene/scene_truck.h"
#include "programs/CG1/scene/scene_donut.h"
#include "programs/CG1/scene/scene_fur.h"
#include "programs/CG1/scene/scene_voxel.h"
#include "programs/CG1/scene/scene_bonfire.h"
#include "programs/CG1/scene/scene_obj.h"
#include "programs/CG1/scene/scene_bezier.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::init()
{
  connectCheckBox(ui->check_animation,true);
  connectCheckBox(ui->check_axis,false);
  connectCheckBox(ui->check_face_normals,false);
  connectCheckBox(ui->check_scene,true);
  connectCheckBox(ui->check_shader,false);
  shaderToggle(false);
  connectCheckBox(ui->check_skydome,true);
  connectCheckBox(ui->check_textures,true);
  connectCheckBox(ui->check_vertex_normals,false);
  connectCheckBox(ui->check_wireframe,false);
  connectCheckBox(ui->check_alt_texture,false);
  connectCheckBox(ui->check_perspective,true);

  connect(ui->check_shader,SIGNAL(toggled(bool)),this,SLOT(shaderToggle(bool)));

  connect(ui->button_hide_interface,SIGNAL(clicked()),this,SLOT(hideTabs()));

  Scene::addScene("**Empty",new Scene(this));
  Scene::addScene("*Obj File",new SceneObj(this));
  Scene::addScene("Tire",new SceneTire(this));
  Scene::addScene("*Bezier",new SceneBezier(this));
  Scene::addScene("Pie",new ScenePie(this));
  Scene::addScene("Truck",new SceneTruck(this));
  Scene::addScene("Donut",new SceneDonut(this));
  Scene::addScene("*Fur",new SceneFur(this));
  Scene::addScene("*Voxel",new SceneVoxel(this));
  Scene::addScene("Campfire",new SceneBonfire(this));
  Scene::setCurrent("**Empty");

  connect(ui->combo_scenes,SIGNAL(currentIndexChanged(QString)),this,SLOT(setScene(QString)));

  ui->combo_scenes->addItems(Scene::scene_list());
  ui->combo_scenes->setCurrentIndex(ui->combo_scenes->findText("**Empty"));
}

void MainWindow::connectCheckBox(QCheckBox *check_box, bool value)
{
  if(check_box == NULL) return;

  connect(check_box,SIGNAL(toggled(bool)),this,SLOT(optionToggled(bool)));
  check_box->setChecked(value);
  Options::instance()->set_option(check_box->objectName(),value);
}

void MainWindow::hideTabs()
{
  if(ui->button_hide_interface->text()=="<"){
    ui->tabWidget->setVisible(false);
    ui->button_hide_interface->setText(">");
  }else{
    ui->tabWidget->setVisible(true);
    ui->button_hide_interface->setText("<");
  }
}

void MainWindow::shaderToggle(bool v)
{
  ui->group_opengl->setEnabled(!v);
}

void MainWindow::optionToggled(bool v)
{
  Options::instance()->set_option(sender()->objectName(),v);
}

void MainWindow::setScene(QString s)
{
  Scene::setCurrent(s);
  if(Scene::current()->controlWidget() != NULL){
    ui->stackedWidget->setCurrentWidget(Scene::current()->controlWidget());
  }

  ui->widget->updateGL();

  ui->list_model->clear();
  ui->list_model->addItems(Model::getList());

  ui->list_material->clear();
  ui->list_material->addItems(Material::getList());

  ui->list_texture->clear();
  ui->list_texture->addItems(Textures::getList());

  ui->list_object->clear();
  ui->list_object->addItems(Scene::current()->getObjectList());
}

void MainWindow::addSceneControlWidget(QWidget *widget)
{
  ui->stackedWidget->addWidget(widget);
}
