#ifndef SCIVIS_H
#define SCIVIS_H

#include <QApplication>

#include "mainwindow.h"

class SciVis : public QApplication
{
  Q_OBJECT
public:
  explicit SciVis(int argc, char *argv[]);

  void clean();

  MainWindow w;
signals:

public slots:

};

#endif // SCIVIS_H
