#ifndef SPACE3D_H
#define SPACE3D_H

#include <QApplication>

class MainWindow;

class Space3D : public QApplication
{
  Q_OBJECT
public:
  explicit Space3D(int argc, char *argv[]);
  virtual ~Space3D();

  MainWindow *main_window;
signals:

public slots:

};

#endif // SPACE3D_H
