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
#include "programs/CG1/scene/scene_multicubes.h"

#include "shaders/phong_shader.h"
#include "shaders/toon_shader.h"

#include "widgets/showmatrixdialog.h"
#include "widgets/add_matrix_dialog.h"

#include <QRegExp>

const QRegExp rotation_regexp = QRegExp("rot\\((\\S+),(\\S+),(\\S+),(\\S+)\\)");
const QRegExp translation_regexp = QRegExp("tra\\((\\S+),(\\S+),(\\S+)\\)");
const QRegExp scale_regexp = QRegExp("sca\\((\\S+),(\\S+),(\\S+)\\)");

const QRegExp ortho_regexp = QRegExp("ort\\((\\S+),(\\S+),(\\S+),(\\S+),(\\S+),(\\S+)\\)");
const QRegExp frustum_regexp = QRegExp("fru\\((\\S+),(\\S+),(\\S+),(\\S+),(\\S+),(\\S+)\\)");

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

  connect(ui->shader_apply,SIGNAL(clicked()),this,SLOT(setShaders()));
  connect(ui->transform_modelview,SIGNAL(indexesMoved(QModelIndexList)),this,SLOT(transformChanged()));
  connect(ui->transform_modelview,SIGNAL(itemSelectionChanged()),this,SLOT(transformChanged()));
  connect(ui->transform_modelview,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(showMatrix(QListWidgetItem*)));
  connect(ui->add_modelview,SIGNAL(clicked()),this,SLOT(addModelviewMatrix()));
  connect(ui->add_projection,SIGNAL(clicked()),this,SLOT(addProjectionMatrix()));
  connect(ui->view_modelview,SIGNAL(clicked()),this,SLOT(viewModelviewMatrix()));
  connect(ui->view_projection,SIGNAL(clicked()),this,SLOT(viewProjectionMatrix()));
  connect(ui->remove_modelview,SIGNAL(clicked()),this,SLOT(removeModelviewMatrix()));
  connect(ui->remove_projection,SIGNAL(clicked()),this,SLOT(removeProjectionMatrix()));

  connect(ui->export_pushButton,SIGNAL(clicked()),ui->gl_widget,SLOT(exportFrameBuffer()));

  ui->shader_premade->addItem("-");
  ui->shader_premade->addItem("Phong");
  ui->shader_premade->addItem("Toon");
  connect(ui->shader_premade,SIGNAL(currentTextChanged(QString)),this,SLOT(setShaderText(QString)));

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
  Scene::addScene("MultiCubes",new SceneMultiCubes(this));
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

void MainWindow::setMatrix(const QString &matrix_name, Busta::Matrix4x4 &output)
{
  int index;
  // ROTATION MATRIX
  index = rotation_regexp.indexIn(matrix_name);
  if(index > -1){
    qDebug() << "Rotation";
    float v[4];
    for(int i=0;i<4;i++){
      v[i] = rotation_regexp.cap(i+1).toFloat();
      qDebug() << v[i];
    }
    output.rotate(v[0],v[1],v[2],v[3]);
  }
  // TRANSLATION MATRIX
  index = translation_regexp.indexIn(matrix_name);
  if(index > -1){
    qDebug() << "Translation";
    float v[3];
    for(int i=0;i<3;i++){
      v[i] = translation_regexp.cap(i+1).toFloat();
      qDebug() << v[i];
    }
    output.translate(v[0],v[1],v[2]);
  }
  // SCALE MATRIX
  index = scale_regexp.indexIn(matrix_name);
  if(index > -1){
    qDebug() << "Scale";
    float v[3];
    for(int i=0;i<3;i++){
      v[i] = scale_regexp.cap(i+1).toFloat();
      qDebug() << v[i];
    }
    output.scale(v[0],v[1],v[2]);
  }
  // ORTHO MATRIX
  index = ortho_regexp.indexIn(matrix_name);
  if(index > -1){
    qDebug() << "Ortho";
    float v[6];
    for(int i=0;i<6;i++){
      v[i] = ortho_regexp.cap(i+1).toFloat();
      qDebug() << v[i];
    }
    output.ortho(v[0],v[1],v[2],v[3],v[4],v[5]);
  }
  // FRUSTUM MATRIX
  index = frustum_regexp.indexIn(matrix_name);
  if(index > -1){
    qDebug() << "Frustum";
    float v[6];
    for(int i=0;i<6;i++){
      v[i] = frustum_regexp.cap(i+1).toFloat();
      qDebug() << v[i];
    }
    output.frustum(v[0],v[1],v[2],v[3],v[4],v[5]);
  }
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
  ui->shader_apply->setVisible(v);
  ui->shader_widget->setVisible(v);
  ui->shader_premade->setVisible(v);

  ui->gl_widget->releaseShader();
}

void MainWindow::optionToggled(bool v)
{
  Options::instance()->set_option(sender()->objectName(),v);
}

void MainWindow::setShaders()
{
  ui->gl_widget->setShaders(ui->text_vertex_shader->toPlainText(),ui->text_frag_shader->toPlainText());
}

void MainWindow::setShaderText(const QString &s)
{
  if(s=="Phong"){
    ui->text_vertex_shader->setText(kPhongShaderVert);
    ui->text_frag_shader->setText(kPhongShaderFrag);
    return;
  }
  if(s=="Toon"){
    ui->text_vertex_shader->setText(kToonShaderVert);
    ui->text_frag_shader->setText(kToonShaderFrag);
    return;
  }
}

void MainWindow::setScene(QString s)
{
  Scene::setCurrent(s);
  if(Scene::current()->controlWidget() != NULL){
    ui->stackedWidget->setCurrentWidget(Scene::current()->controlWidget());
  }

  ui->gl_widget->updateGL();

  ui->list_model->clear();
  ui->list_model->addItems(Model::getList());

  ui->list_material->clear();
  ui->list_material->addItems(Material::getList());

  ui->list_texture->clear();
  ui->list_texture->addItems(Textures::getList());

  ui->list_object->clear();
  ui->list_object->addItems(Scene::current()->getObjectList());

  if(Scene::current()!=NULL){
    Scene::current()->setGuiMatrix(interface_modelview,interface_projection);
  }
}

void MainWindow::transformChanged()
{
  // MODELVIEW MATRIX
  interface_modelview.loadIdentity();
  qDebug() << "Modelview Matrix";
  foreach(QListWidgetItem* list_item, ui->transform_modelview->findItems("*", Qt::MatchWildcard))
  {
    setMatrix(list_item->text(),interface_modelview);
  }
  // PROJECTION MATRIX
  interface_projection.loadIdentity();
  qDebug() << "Projection Matrix";
  foreach(QListWidgetItem* list_item, ui->transform_projection->findItems("*", Qt::MatchWildcard))
  {
   setMatrix(list_item->text(),interface_projection);
  }

  Options::instance()->force_change_option();

  if(Scene::current()!=NULL){
    Scene::current()->setGuiMatrix(interface_modelview,interface_projection);
  }
}

void MainWindow::showMatrix(QListWidgetItem* item)
{
  if(item==NULL) return;
  Busta::Matrix4x4 matrix;
  setMatrix(item->text(),matrix);
  ShowMatrixDialog show_matrix(matrix,this);
  show_matrix.exec();
}

void MainWindow::addModelviewMatrix()
{
  AddMatrixDialog matrix_dialog;
  int code = matrix_dialog.exec();
  if(code == QDialog::Accepted){
    QString res = matrix_dialog.resulting_string();
    if(!res.isEmpty()){
      ui->transform_modelview->addItem(res);
      transformChanged();
    }
  }
}

void MainWindow::addProjectionMatrix()
{
  AddMatrixDialog matrix_dialog;
  int code = matrix_dialog.exec();
  if(code == QDialog::Accepted){
    QString res = matrix_dialog.resulting_string();
    if(!res.isEmpty()){
      ui->transform_projection->addItem(res);
      transformChanged();
    }
  }
}

void MainWindow::viewModelviewMatrix()
{
  if(ui->transform_modelview->currentItem()!=NULL){
    showMatrix(ui->transform_modelview->currentItem());
  }
}

void MainWindow::viewProjectionMatrix()
{
  if(ui->transform_projection->currentItem()!=NULL){
    showMatrix(ui->transform_projection->currentItem());
  }
}

void MainWindow::removeModelviewMatrix()
{
  if(ui->transform_modelview->currentItem()!=NULL){
    qDebug() << "Removing";
    QListWidgetItem *item = ui->transform_modelview->takeItem(ui->transform_modelview->currentIndex().row());
    delete item;
    transformChanged();
  }
}

void MainWindow::removeProjectionMatrix()
{
  if(ui->transform_projection->currentItem()!=NULL){
    qDebug() << "Removing";
    QListWidgetItem *item = ui->transform_projection->takeItem(ui->transform_projection->currentIndex().row());
    delete item;
    transformChanged();
  }
}

void MainWindow::addSceneControlWidget(QWidget *widget)
{
  ui->stackedWidget->addWidget(widget);
}
