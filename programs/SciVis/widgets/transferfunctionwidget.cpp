#include "transferfunctionwidget.h"

#include <QPainter>
#include <QLinearGradient>
#include <QMouseEvent>
#include <QDebug>
#include <QVector2D>
#include <QColorDialog>

const int kEllipseRad = 5;

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

  move_index = -1;
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
    painter.drawEllipse(circles[i].first,kEllipseRad,kEllipseRad);
  }

}

void TransferFunctionWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
  QVector2D pos_v = QVector2D(e->pos());
  for(int i=0;i<tf.size();i++){
    QPointF circ_center = normalizedToWidgetCoord(tf.getIndex(i).value,tf.getIndex(i).color.alphaF());
    float dist = (pos_v-QVector2D(circ_center)).length();
    if(dist<=kEllipseRad){
        tf.remove(i);
        update();
        e->accept();
        return;
    }
  }

  QPointF p = getNormalizedFromWidgetCoord(e->pos());
  QColor color = QColorDialog::getColor();
  if(!color.isValid()) return;
  color.setAlphaF(p.y());
  tf.add(p.x(),color);
  tf.sort();
  update();
  e->accept();
}

void TransferFunctionWidget::mousePressEvent(QMouseEvent *e)
{
  QVector2D pos_v = QVector2D(e->pos());
  for(int i=0;i<tf.size();i++){
    QPointF circ_center = normalizedToWidgetCoord(tf.getIndex(i).value,tf.getIndex(i).color.alphaF());
    float dist = (pos_v-QVector2D(circ_center)).length();
    if(dist<=kEllipseRad){
      move_index = i;
    }
  }
}

void TransferFunctionWidget::mouseReleaseEvent(QMouseEvent *e)
{
  if(move_index!=-1){
    move_index = -1;
    tf.sort();
    update();
  }
}

void TransferFunctionWidget::mouseMoveEvent(QMouseEvent *e)
{
  if(move_index != -1){
    tf.moveIndex(move_index,getNormalizedFromWidgetCoord(e->pos()));
    update();
  }
}

QPointF TransferFunctionWidget::normalizedToWidgetCoord(float x, float y)
{
  QPointF p(x*(this->width()-1),(1.0f-y)*(this->height()-1));
  return p;
}

QPointF TransferFunctionWidget::getNormalizedFromWidgetCoord(QPoint p)
{
  QPointF ret = QPointF( float(p.x())/(rect().width()),1-float(p.y())/(rect().height()) );
  qDebug() << "ret" << ret;
  return ret;
}
