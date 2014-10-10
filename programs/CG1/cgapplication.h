#ifndef CGAPPLICATION_H
#define CGAPPLICATION_H

#include <QApplication>
class MainWindow;

class CGApplication : public QApplication
{
public:
  explicit CGApplication(int argc, char *argv[]);
  virtual ~CGApplication();

  MainWindow *getMainWindow();

private:
  MainWindow *main_window_;
};

#endif // CGAPPLICATION_H
