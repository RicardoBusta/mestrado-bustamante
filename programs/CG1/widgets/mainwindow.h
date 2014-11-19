#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCheckBox>
#include <QListWidgetItem>

#include "programs/CG1/utils/options.h"
#include "busta_libs/common_structures/matrix4x4.h"

#define DECLARE_TOGGLE_CHECK(c_name)\
    void toggle_(c_name)(bool v)

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  void addSceneControlWidget(QWidget *widget);

  void init();
private:
  Ui::MainWindow *ui;

  void connectCheckBox(QCheckBox *check_box, bool value);

  Busta::Matrix4x4 interface_modelview;
  Busta::Matrix4x4 interface_projection;

  void setMatrix(const QString &matrix_name, Busta::Matrix4x4 &output);
private slots:
  void hideTabs();

  void shaderToggle(bool v);

  void optionToggled(bool v);

  void setShaders();
  void setShaderText(const QString &s);

  void setScene(QString s);

  void transformChanged();
  void showMatrix(QListWidgetItem * item);
  void addModelviewMatrix();
  void addProjectionMatrix();
  void viewModelviewMatrix();
  void viewProjectionMatrix();
};

#undef DECLARE_TOGGLE_CHECK

#endif // MAINWINDOW_H
