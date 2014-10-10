#include "random.h"

#include <QtGlobal>
#include <QTime>

bool Random::initialized_ = false;

int Random::get()
{
  if(initialized_ == false){
    qsrand(QTime::currentTime().msec());
    initialized_ = true;
  }

  return qrand();
}

float Random::getF()
{
  return (float(get())/float(RAND_MAX));
}

Random::Random()
{
}
