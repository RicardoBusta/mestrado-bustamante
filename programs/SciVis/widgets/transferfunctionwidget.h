#ifndef TRANSFERFUNCTIONWIDGET_H
#define TRANSFERFUNCTIONWIDGET_H

#include <QWidget>

#include "algorithm/transferfunction.h"

class TransferFunctionWidget : public QWidget
{
  Q_OBJECT
public:
  TransferFunctionWidget(QWidget *parent);

  void paintEvent(QPaintEvent *e);

  void mouseDoubleClickEvent(QMouseEvent *e);

  TransferFunction tf;

private:
  QPointF normalizedToWidgetCoord(float x, float y);
  QPointF getNormalizedFromWidgetCoord(QPoint p);
};

#endif // TRANSFERFUNCTIONWIDGET_H
