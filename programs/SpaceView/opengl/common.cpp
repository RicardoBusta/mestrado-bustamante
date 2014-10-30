#include "opengl/common.h"

QString ReadValidLine(QTextStream &in){
  QString out = in.readLine();
  while(out.startsWith('#')){
    //    qDebug() << out;
    out = in.readLine();
  }
  return out;
}
