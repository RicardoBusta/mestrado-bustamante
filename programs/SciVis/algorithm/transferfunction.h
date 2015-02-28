#ifndef TRANSFERFUNCTION_H
#define TRANSFERFUNCTION_H

#include <QVector>
#include <QColor>

class TransferFunctionElement{
public:
  TransferFunctionElement();
  TransferFunctionElement(float v, QColor c):
    value(v),color(c){}
  float value;
  QColor color;
  bool operator<(const TransferFunctionElement &e) const;
};

class TransferFunction
{
public:
  TransferFunction();

  QColor get(float value) const;
  TransferFunctionElement getIndex(int index) const;
  int size() const;

  void add(float value, QColor color);

  void remove(int index);

  void clear();

  void moveIndex(int index, const QPointF &point);

  //use once before the first get or after the last add.
  void sort();

  void setMax(float m);
  void setMin(float m);
private:
  float max;
  float min;

  QVector< TransferFunctionElement > function;
  QColor interpColor(const float &v, const QColor &c1, const QColor &c2) const;
};

#endif // TRANSFERFUNCTION_H
