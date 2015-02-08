#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class AAVMainWindow;
}

class AAVMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit AAVMainWindow(QWidget *parent = 0);
  ~AAVMainWindow();

private:
  Ui::AAVMainWindow *ui;
};

#endif // MAINWINDOW_H
