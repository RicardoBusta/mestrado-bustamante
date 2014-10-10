#include "scene_fur.h"

#include "ui_fur_widget.h"

const int num_layers = 50;
const int num_layers_0 = 1;
const int num_layers_1 = 30;
const float fur_size = 0.5;

SceneFur::SceneFur(QObject *parent):
  Scene(parent)
{
}

SceneFur::~SceneFur()
{
}

void SceneFur::setup_spec()
{
  Model::load(":/model/fur.obj");
  Model::load(":/model/skydome.obj");

  Object *fur_eyes = Object::create("Fur Eyes","fur_eyes");
  fur_eyes->setAltTexture("fur_alt.png");
  objects_.push_back(fur_eyes);

  fur_layer_.resize(num_layers);

//  const float gravity = -0.0003f*gravity_;
//  const float velocity = 0.001f*speed_;

  for(int i=0;i<fur_layer_.size();i++){
    int level;
    if(i < num_layers_0){
      level = 0;
    }else if(i<num_layers_1){
      level = 1;
    }else{
      level = 2;
    }
    Object *fur_layer = Object::create(QString("Fur layer %1").arg(i),QString("fur_level_%1").arg(level));
    fur_layer_[i] = fur_layer;
    fur_layer->setAltTexture("fur_alt.png");
    objects_.push_back(fur_layer);
  }

  calcScene();

  skybox_ = Object::create("Skydome","skydome");
}

void SceneFur::buildControlWidget()
{
  Ui::FurWidget *ui = new Ui::FurWidget;
  ui->setupUi(control_widget_);

  connect(ui->spin_gravity,SIGNAL(valueChanged(double)),this,SLOT(changeGravity(double)));
  connect(ui->spin_speed,SIGNAL(valueChanged(double)),this,SLOT(changeSpeed(double)));
  connect(ui->check_fur,SIGNAL(toggled(bool)),this,SLOT(toggleFur(bool)));

  ui->spin_gravity->setValue(1.0);
  ui->spin_speed->setValue(1.0);
  ui->check_fur->setChecked(true);

}

void SceneFur::calcScene()
{
  qDebug() << "calc scene";
  const float gravity = -0.0003f*gravity_;
  const float velocity = 0.001f*speed_;

  for(int i=0;i<fur_layer_.size();i++){
    fur_layer_[i]->setScale(1.0 + (fur_size/float(fur_layer_.size()))*i);
    int alpha = 255*(1.0 - (1.0/float(fur_layer_.size()))*i);
    int tone = 255.0 - alpha/2;
    float displacement = velocity*i + (gravity*i*i)/2;
    fur_layer_[i]->setCustomColor(QColor(tone,tone,tone,alpha));
    fur_layer_[i]->setPosition(QVector3D(0,displacement,0));
  }
}

void SceneFur::changeGravity(double g)
{
  gravity_ = g;
  calcScene();
}

void SceneFur::changeSpeed(double s)
{
  speed_ = s;
  calcScene();
}

void SceneFur::toggleFur(bool f)
{
  for(int i=1;i<fur_layer_.size();i++){
    fur_layer_[i]->setVisible(f);
  }

  calcScene();
}
