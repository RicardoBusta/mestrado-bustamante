#include "transferfunction.h"

TransferFunction::TransferFunction()
{
  max = 300;
  min = 0;
}

QColor TransferFunction::get(float value) const
{
  float normal_value = (value-min)/(max-min);

  if(function.isEmpty()){
    return QColor(0,0,0,0);
  }
  if(function.size()==1){
    return function.first().color;
  }
  if(normal_value <= function.first().value){
    return function.first().color;
  }
  if(normal_value >= function.last().value){
    return function.last().color;
  }

  for(int i=0;i+1<function.size();i++){
    float v1 = function[i].value;
    float v2 = function[i+1].value;
    if(normal_value >= v1 && normal_value <= v2){
      float v = (normal_value-v1)/(v2-v1);
      return interpColor(v,function[i].color,function[i+1].color);
    }
  }
  return QColor(0,0,0);
}

TransferFunctionElement TransferFunction::getIndex(int index) const
{
  if(index>=0 && index<function.size()){
    return function[index];
  }
  return TransferFunctionElement(0,QColor());
}

int TransferFunction::size() const
{
  return function.size();
}

void TransferFunction::add(float value, QColor color)
{
  function.push_back(TransferFunctionElement(value,color));
}

void TransferFunction::remove(int index)
{
  function.removeAt(index);
}

void TransferFunction::clear()
{
  function.clear();
}

void TransferFunction::sort()
{
  qSort(function);
}

void TransferFunction::setMax(float m)
{
  max = m;
}

void TransferFunction::setMin(float m)
{
  min = m;
}

QColor TransferFunction::interpColor(const float &v, const QColor &c1, const QColor &c2) const
{
  QColor c(
        int(255.0f*(c1.redF()*(1-v) + c2.redF()*v)),
        int(255.0f*(c1.greenF()*(1-v) + c2.greenF()*v)),
        int(255.0f*(c1.blueF()*(1-v) + c2.blueF()*v)),
        int(255.0f*(c1.alphaF()*(1-v) + c2.alphaF()*v))
        );
  return c;
}


TransferFunctionElement::TransferFunctionElement()
{

}

bool TransferFunctionElement::operator<(const TransferFunctionElement &e) const
{
  return (value<e.value);
}
