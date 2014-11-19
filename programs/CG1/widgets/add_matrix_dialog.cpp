#include "add_matrix_dialog.h"
#include "ui_add_matrix_dialog.h"

AddMatrixDialog::AddMatrixDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::AddMatrixDialog)
{
  ui->setupUi(this);

  widgets.push_back(qMakePair(ui->label_1,ui->doubleSpinBox_1));
  widgets.push_back(qMakePair(ui->label_2,ui->doubleSpinBox_2));
  widgets.push_back(qMakePair(ui->label_3,ui->doubleSpinBox_3));
  widgets.push_back(qMakePair(ui->label_4,ui->doubleSpinBox_4));
  widgets.push_back(qMakePair(ui->label_5,ui->doubleSpinBox_5));
  widgets.push_back(qMakePair(ui->label_6,ui->doubleSpinBox_6));

  for(int i=0;i<widgets.size();i++){
    connect(widgets[i].second,SIGNAL(valueChanged(double)),this,SLOT(build_string()));
  }
  connect(ui->comboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(setParameters(QString)));
}

AddMatrixDialog::~AddMatrixDialog()
{
  delete ui;
}

QString AddMatrixDialog::resulting_string() const
{
  return resulting_string_;
}

void AddMatrixDialog::setParameters(const QVector<QString> &params)
{
  for(int i=0;i<widgets.size();i++){
    if(i<params.size()){
      widgets[i].first->setText(params[i]);
      widgets[i].first->setEnabled(true);
      widgets[i].second->setEnabled(true);
    }else{
      widgets[i].first->setText("...");
      widgets[i].first->setEnabled(false);
      widgets[i].second->setEnabled(false);
    }
  }
}

void AddMatrixDialog::build_string()
{
  QString type = ui->comboBox->currentText();
  QString str;
  if(type=="Rotation"){
    str = QString("rot(%1,%2,%3,%4)")
          .arg(ui->doubleSpinBox_1->value())
          .arg(ui->doubleSpinBox_2->value())
          .arg(ui->doubleSpinBox_3->value())
          .arg(ui->doubleSpinBox_4->value());
  }else
  if(type=="Translation"){
    str = QString("tra(%1,%2,%3)")
          .arg(ui->doubleSpinBox_1->value())
          .arg(ui->doubleSpinBox_2->value())
          .arg(ui->doubleSpinBox_3->value());
  }else
  if(type=="Scale"){
    str = QString("sca(%1,%2,%3)")
          .arg(ui->doubleSpinBox_1->value())
          .arg(ui->doubleSpinBox_2->value())
          .arg(ui->doubleSpinBox_3->value());
  }else
  if(type=="Ortho"){
    str = QString("ort(%1,%2,%3,%4,%5,%6)")
          .arg(ui->doubleSpinBox_1->value())
          .arg(ui->doubleSpinBox_2->value())
          .arg(ui->doubleSpinBox_3->value())
          .arg(ui->doubleSpinBox_4->value())
          .arg(ui->doubleSpinBox_5->value())
          .arg(ui->doubleSpinBox_6->value());
  }else
  if(type=="Frustum"){
    str = QString("fru(%1,%2,%3,%4,%5,%6)")
          .arg(ui->doubleSpinBox_1->value())
          .arg(ui->doubleSpinBox_2->value())
          .arg(ui->doubleSpinBox_3->value())
          .arg(ui->doubleSpinBox_4->value())
          .arg(ui->doubleSpinBox_5->value())
          .arg(ui->doubleSpinBox_6->value());
  }
  ui->label->setText(str);
  resulting_string_ = str;
}

void AddMatrixDialog::setParameters(QString type)
{
  QVector<QString> parameters;
  if(type=="Rotation"){
    parameters.push_back("angle");
    parameters.push_back("x");
    parameters.push_back("y");
    parameters.push_back("z");
    setParameters(parameters);
  }else
  if(type=="Translation"){
    parameters.push_back("x");
    parameters.push_back("y");
    parameters.push_back("z");
    setParameters(parameters);
  }else
  if(type=="Scale"){
    parameters.push_back("x");
    parameters.push_back("y");
    parameters.push_back("z");
    setParameters(parameters);
  }else
  if(type=="Ortho"){
    parameters.push_back("left");
    parameters.push_back("right");
    parameters.push_back("bottom");
    parameters.push_back("top");
    parameters.push_back("near");
    parameters.push_back("far");
    setParameters(parameters);
  }else
  if(type=="Frustum"){
    parameters.push_back("left");
    parameters.push_back("right");
    parameters.push_back("bottom");
    parameters.push_back("top");
    parameters.push_back("near");
    parameters.push_back("far");
    setParameters(parameters);
  }else{
    setParameters(parameters);
  }
  build_string();
}
