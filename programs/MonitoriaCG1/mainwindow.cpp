#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->opengl_widget->SetModelRef(&models_);

  Model m;
  m = Model::LoadTriangle();
  models_.insert(m.name(), m);
  m = Model::LoadCube();
  models_.insert(m.name(), m);

  UpdateModels();
  ui->comboBox->setCurrentText(m.name());

  ui->splitter->setStretchFactor(0, 1);
  ui->splitter->setStretchFactor(1, 5);

  QObject::connect(ui->hide_pushButton, SIGNAL(clicked()), this,
                   SLOT(ToggleHideCurrentModel()));
  QObject::connect(ui->texture_pushButton, SIGNAL(clicked()), ui->opengl_widget,
                   SLOT(LoadTexture()));
  QObject::connect(ui->perspective_pushButton, SIGNAL(clicked()),
                   ui->opengl_widget, SLOT(TogglePerspective()));
  QObject::connect(ui->load_fsh_pushButton, SIGNAL(clicked()), this,
                   SLOT(LoadFsh()));
  QObject::connect(ui->load_vsh_pushButton, SIGNAL(clicked()), this,
                   SLOT(LoadVsh()));
  QObject::connect(ui->load_obj_pushButton, SIGNAL(clicked()), this,
                   SLOT(LoadObjModel()));
  QObject::connect(ui->compile_shaders_pushButton,SIGNAL(clicked()),this,SLOT(CompileShaders()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::ToggleHideCurrentModel() {
  QString name = ui->comboBox->currentText();
  if (models_.contains(name)) {
    models_[name].ToggleHide();
    ui->opengl_widget->update();
  }
}

void MainWindow::UpdateModels() {
  ui->comboBox->blockSignals(true);
  ui->comboBox->clear();

  foreach (const Model &m, models_) { ui->comboBox->addItem(m.name()); }
  ui->comboBox->blockSignals(false);
}

void MainWindow::LoadObjModel() {
  QString filename = QFileDialog::getOpenFileName(
      this, "Open Wavefront Obj File", ".", "Wavefront Obj (*.obj)");
}

void MainWindow::LoadVsh() {
  QString filename = QFileDialog::getOpenFileName(
      this, "Open Vertex Shader File", ".", "Vertex Shader (*.vsh *.vert)");
}

void MainWindow::LoadFsh() {
  QString filename = QFileDialog::getOpenFileName(
      this, "Open Fragment Shader File", ".", "Fragment Shader (*.fsh *.frag)");
}

void MainWindow::CompileShaders() {
  ui->opengl_widget->SetShaders(ui->vert_textEdit->toPlainText(),
                                ui->frag_textEdit->toPlainText());
}
