#ifndef LOADINGPROGRESS_H
#define LOADINGPROGRESS_H

#include <QWidget>

namespace Ui {
class LoadingProgress;
}

class LoadingProgress : public QWidget
{
  Q_OBJECT

public:
  explicit LoadingProgress(QWidget *parent = 0);
  ~LoadingProgress();

private:
  Ui::LoadingProgress *ui;
};

#endif // LOADINGPROGRESS_H
