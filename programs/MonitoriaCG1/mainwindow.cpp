#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->opengl_widget->SetModelRef(&models_);

  Model m;
  m = Model::LoadTriangle();
  models_.insert(m.name(),m);
  m = Model::LoadCube();
  models_.insert(m.name(),m);

  UpdateModels();
  ui->comboBox->setCurrentText(m.name());

  ui->splitter->setStretchFactor(0,1);
  ui->splitter->setStretchFactor(1,5);

  QObject::connect(ui->hide_pushButton,SIGNAL(clicked(bool)),this,SLOT(ToggleHideCurrentModel()));
  QObject::connect(ui->texture_pushButton,SIGNAL(clicked(bool)),ui->opengl_widget,SLOT(LoadTexture()));
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::ToggleHideCurrentModel() {
  QString name = ui->comboBox->currentText();
  if(models_.contains(name)){
    models_[name].ToggleHide();
    ui->opengl_widget->update();
  }
}

void MainWindow::UpdateModels() {
  ui->comboBox->blockSignals(true);
  ui->comboBox->clear();

  foreach(const Model &m, models_){
    ui->comboBox->addItem(m.name());
  }
  ui->comboBox->blockSignals(false);
}
