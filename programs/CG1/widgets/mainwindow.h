#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCheckBox>

#include "programs/CG1/utils/options.h"

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

private slots:
  void hideTabs();

  void shaderToggle(bool v);

  void optionToggled(bool v);

  void setScene(QString s);
};

#undef DECLARE_TOGGLE_CHECK

#endif // MAINWINDOW_H
