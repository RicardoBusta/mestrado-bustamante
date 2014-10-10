#include "scene_truck.h"

#include "programs/CG1/animation/animation_spin.h"

#include "ui_truck_widget.h"

SceneTruck::SceneTruck(QObject *parent):
  Scene(parent)
{
}

void SceneTruck::setup_spec()
{
  //Model::load(":/model/tire.obj");
  Model::load(":/model/skydome.obj");
  QStringList pickup_objects = Model::load(":/model/pickup.obj");

  Object *tire[4];
  QVector3D pos[4]={
    QVector3D(1,0,1.85),
    QVector3D(-1,0,1.85),
    QVector3D(1,0,-1.1),
    QVector3D(-1,0,-1.1)
  };

  QVector3D rot[4]={
    QVector3D(0,180,0),
    QVector3D(0,0,0),
    QVector3D(0,180,0),
    QVector3D(0,0,0),
  };

  int direction[4]={
    -1,
    1,
    -1,
    1
  };

  QVector3D truck_translate = QVector3D(0,-0.4,0);

  Object *interior = Object::create("Interior","interior");
  interior->setPosition(truck_translate);
  Object *exterior = Object::create("Exterior","exterior");
  exterior->setPosition(truck_translate);
  exterior->setAltTexture("pickup_exterior_alt.png");
  Object *glass = Object::create("Glass","glass");
  glass->setPosition(truck_translate);

  objects_.push_back(interior);
  objects_.push_back(exterior);
  objects_.push_back(glass);


  for(int i=0;i<4;i++){
    tire[i] = Object::create(QString("Tire %1").arg(i),"pickup_tire");
    tire[i]->addAnimation(new AnimationSpin(90*i,10*direction[i],AnimationSpin::SPIN_X));
    tire[i]->setPosition(pos[i]);
    tire[i]->setEulerRotation(rot[i]);
    objects_.push_back(tire[i]);
  }

  skybox_ = Object::create("Skydome","skydome");
}

void SceneTruck::buildControlWidget()
{
 Ui::TruckWidget *ui = new Ui::TruckWidget;
 ui->setupUi(control_widget_);

 connect(ui->checkBox,SIGNAL(toggled(bool)),this,SLOT(toggleCameraConstraint(bool)));

 ui->checkBox->setChecked(true);
}

void SceneTruck::toggleCameraConstraint(bool v)
{
  camera_constraint_ = v;
}

void SceneTruck::applyCameraConstraint()
{
  if(!camera_constraint_) return;

 if(rot_x_ > 90) {
   rot_x_ = 90;
 }
 if(rot_x_ < 10){
   rot_x_ = 10;
 }
}

