#include "programs/CG2/widgets/mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>
#include <QDebug>
#include <QLabel>
#include <QMouseEvent>

#include "programs/CG2/constants.h"
#include "programs/CG2/scene/scene.h"
#include "programs/CG2/widgets/glwidget.h"
#include "programs/CG2/widgets/raytracingwidget.h"
#include "programs/CG2/widgets/outerviewwidget.h"
#include "programs/CG2/widgets/raytracingresultviewerwidget.h"

MainWindow::MainWindow(Scene *scene, QWidget *parent) :
  QMainWindow(parent),
  ui_(new Ui::MainWindow),
  scene_(scene)
{
  ui_->setupUi(this);

  gl_widget_ = new GLWidget(scene_);
  ui_->opengl_box->layout()->addWidget(gl_widget_);
  //  connect(gl_widget_,SIGNAL(Changed()),this,SLOT(SceneChanged()));

  outer_view_widget_ = new OuterViewWidget(scene_);
  ui_->outerview_box->layout()->addWidget(outer_view_widget_);
  connect(outer_view_widget_,SIGNAL(Changed()),this,SLOT(SceneChanged()));

  ray_tracing_widget_ = new RayTracingWidget(scene_);
  ui_->raytracing_box->layout()->addWidget(ray_tracing_widget_);
  connect(ray_tracing_widget_,SIGNAL(Changed()),this,SLOT(SceneChanged()));
  connect(ui_->recursion_spinBox,SIGNAL(valueChanged(int)),ray_tracing_widget_,SLOT(RayTracingLevel(int)));

  const int default_fov_slider = ((100*(kDefaultFov-kMinFov))/(kMaxFov-kMinFov));
  ui_->fov_slider->setValue(default_fov_slider);
  const int default_near_slider = ((100*(kDefaultNear-kMinNear))/(kMaxNear-kMinNear));
  ui_->near_slider->setValue(default_near_slider);
  const int default_far_slider = ((100*(kDefaultFar-kMinFar))/(kMaxFar-kMinFar));
  ui_->far_slider->setValue(default_far_slider);

  connect(ui_->fov_slider,SIGNAL(valueChanged(int)),this,SLOT(SetFov(int)));
  connect(ui_->near_slider,SIGNAL(valueChanged(int)),this,SLOT(SetNear(int)));
  connect(ui_->far_slider,SIGNAL(valueChanged(int)),this,SLOT(SetFar(int)));
  connect(ui_->light_check,SIGNAL(toggled(bool)),this,SLOT(SetLight(bool)));
  connect(ui_->track_ray_check,SIGNAL(toggled(bool)),this,SLOT(SetTrackRay(bool)));
  SetTrackRay(ui_->track_ray_check->isChecked());
  connect(ui_->fast_render_check,SIGNAL(toggled(bool)),ray_tracing_widget_,SLOT(ToggleFastRenderOnly(bool)));
  ray_tracing_widget_->ToggleFastRenderOnly(ui_->fast_render_check->isChecked());
  //  connect(ui_->image_size_comboBox,SIGNAL(currentIndexChanged(int)),ray_tracing_widget_,SLOT(SelectImageSize(int)));
  //  ray_tracing_widget_->SelectImageSize(ui_->image_size_comboBox->currentIndex());

  connect(ui_->scene_comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(LoadScene(int)));
      //  connect(ui_->load1_pushButton,SIGNAL(clicked()),this,SLOT(LoadScene1()));
      //  connect(ui_->load2_pushButton_2,SIGNAL(clicked()),this,SLOT(LoadScene2()));

      //  connect(gl_widget_,SIGNAL(Moving(bool)),ray_tracing_widget_,SLOT(SetMoving(bool)));

      connect(gl_widget_,SIGNAL(MouseMoved(QMouseEvent*)),ray_tracing_widget_,SLOT(MouseMoved(QMouseEvent*)));
  connect(gl_widget_,SIGNAL(MousePressed(QMouseEvent*)),ray_tracing_widget_,SLOT(MousePressed(QMouseEvent*)));
  connect(gl_widget_,SIGNAL(MouseReleased(QMouseEvent*)),ray_tracing_widget_,SLOT(MouseReleased(QMouseEvent*)));
  connect(gl_widget_,SIGNAL(Wheel(QWheelEvent*)),ray_tracing_widget_,SLOT(Wheel(QWheelEvent*)));

  connect(ui_->render_button,SIGNAL(clicked()),this,SLOT(FinalRender()));

  SceneChanged();
}

MainWindow::~MainWindow()
{
  delete ui_;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
  Q_UNUSED(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
  if(event->button() == Qt::LeftButton){
    event->accept();
  }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
  Q_UNUSED(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
  Q_UNUSED(event);
}

void MainWindow::SceneChanged()
{
  scene_->calcMatrixes();

  ray_tracing_widget_->TryUpdate();
  outer_view_widget_->updateGL();
  gl_widget_->updateGL();
  //  ui->widget_canvas->hide();
  //  this->resize(800,800);


  ui_->fov_label->setText(QString::number(scene_->fov)+"º");
  ui_->near_label->setText(QString::number(scene_->near_plane_z));
  ui_->far_label->setText(QString::number(scene_->far_plane_z));
  //qDebug() << "=====";
  //  qDebug() << scene_->modelview_matrix[0] << scene_->modelview_matrix[1] << scene_->modelview_matrix[2] << scene_->modelview_matrix[3];
  //  qDebug() << scene_->modelview_matrix[4] << scene_->modelview_matrix[5] << scene_->modelview_matrix[6] << scene_->modelview_matrix[7];
  //  qDebug() << scene_->modelview_matrix[8] << scene_->modelview_matrix[9] << scene_->modelview_matrix[10] << scene_->modelview_matrix[11];
  //  qDebug() << scene_->modelview_matrix[12] << scene_->modelview_matrix[13] << scene_->modelview_matrix[14] << scene_->modelview_matrix[15];
}

void MainWindow::SetFov(const int value)
{
  scene_->fov = ((kMaxFov-kMinFov)*(float(value)/100.0f))+kMinFov;
  scene_->calcFrustum();
  SceneChanged();
}

void MainWindow::SetNear(const int value)
{
  scene_->near_plane_z = ((kMaxNear-kMinNear)*(float(value)/100.0f))+kMinNear;
  scene_->calcFrustum();
  SceneChanged();
}

void MainWindow::SetFar(const int value)
{
  scene_->far_plane_z = ((kMaxFar-kMinFar)*(float(value)/100.0f))+kMinFar;
  scene_->calcFrustum();
  SceneChanged();
}

void MainWindow::SetLight(const bool value)
{
  scene_->calculate_advanced_light = value;
  SceneChanged();
}

void MainWindow::SetTrackRay(const bool value)
{
  scene_->track_one_ray = value;
  SceneChanged();
}

void MainWindow::LoadScene(int s)
{
  scene_->clearScene();
  switch(s){
  case 1:
    scene_->loadDefaultScene1();
    break;
  case 2:
    scene_->loadDefaultScene2();
    break;
  default:
    scene_->loadScene(ui_->scene_comboBox->currentText());
    break;
  }
  SceneChanged();
}

void MainWindow::FinalRender()
{
  QStringList val = ui_->image_size->currentText().split("x");
  QSize size(val[0].toInt(),val[1].toInt());

  RayTracingResultViewerWidget *wid = new RayTracingResultViewerWidget(scene_,size,ui_->recursion_spinBox->value());
  wid->setStyleSheet(this->styleSheet());
  wid->setModal(true);
  wid->exec();
  delete wid;
}
