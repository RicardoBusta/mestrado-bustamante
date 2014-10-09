#include "common.h"

#include <cmath>

QString ReadValidLine(QTextStream &in){
  QString out = in.readLine();
  while(out.startsWith('#')){
    //    qDebug() << out;
    out = in.readLine();
  }
  return out;
}

int fat(int n){
  if(n>0){
    return n*fat(n-1);
  }else{
    return 1;
  }
}

float binomial(int n, int i){
  return ( float(fat(n)) / float(fat(i) * fat(n-i)) );
}

float bernstein(float u, int n, int i){
  return (binomial(n,i) * pow(u,i) * pow(1.0f-u,n-i));
}
