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
  void mousePressEvent(QMouseEvent *e);
  void mouseReleaseEvent(QMouseEvent *e);
  void mouseMoveEvent(QMouseEvent *e);

  TransferFunction tf;

  int move_index;

private:
  QPointF normalizedToWidgetCoord(float x, float y);
  QPointF getNormalizedFromWidgetCoord(QPoint p);
};

#endif // TRANSFERFUNCTIONWIDGET_H
