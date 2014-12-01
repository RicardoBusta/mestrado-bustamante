#include "transferfunctionwidget.h"

#include <QPainter>
#include <QLinearGradient>

TransferFunctionWidget::TransferFunctionWidget(QWidget *parent):
  QWidget(parent)
{
  tf.setMax(300);
  tf.setMin(0);
  tf.add(0,QColor(0,0,0,0));
  tf.add(0.3,QColor(0,0,0,0));
  tf.add(0.333,QColor(0xff,0xff,0,0x09));
  tf.add(0.5,QColor(0xff,0x0,0,0x09));
  tf.add(0.7,QColor(0xff,0xff,0xff,0x09));
  tf.add(1.0,QColor(0x00,0x00,0x00,0x00));

  tf.sort();
}

void TransferFunctionWidget::paintEvent(QPaintEvent *e)
{
  QPainter painter(this);

  painter.setBrush(QBrush(QColor(230,230,230),Qt::SolidPattern));
  painter.drawRect(this->rect().adjusted(0,0,-1,-1));
  painter.setBrush(QBrush(QColor(200,200,200),Qt::DiagCrossPattern));
  painter.drawRect(this->rect().adjusted(0,0,-1,-1));

  QPolygonF poly;
  QLinearGradient grad = QLinearGradient(rect().bottomLeft(),rect().bottomRight());

  QVector< QPair<QPointF,QColor> > circles;

  for(int i=0;i<tf.size();i++){
    float val = tf.getIndex(i).value;
    QColor col = tf.getIndex(i).color;
    QColor col_no_alpha = col;
    col_no_alpha.setAlpha(255);
    float alpha = col.alphaF();

    painter.setPen(Qt::black);
    painter.setBrush(col_no_alpha);
    QPointF pos = normalizedToWidgetCoord(val,alpha);
    circles.push_back( qMakePair(pos, col_no_alpha) );
    poly.push_back(pos);
    grad.setColorAt(val,col);
  }

  poly.push_back(normalizedToWidgetCoord(1,0));
  poly.push_back(normalizedToWidgetCoord(0,0));

  painter.setPen(QPen(Qt::black,2));
  painter.setBrush(QBrush(grad));
  painter.drawPolygon(poly);

  for(int i=0;i<circles.size();i++){
    painter.setBrush(circles[i].second);
    painter.drawEllipse(circles[i].first,5,5);
  }

}

void TransferFunctionWidget::mouseDoubleClickEvent(QMouseEvent *e)
{

}

QPointF TransferFunctionWidget::normalizedToWidgetCoord(float x, float y)
{
  QPointF p(x*(this->width()-1),(1.0f-y)*(this->height()-1));
  return p;
}
