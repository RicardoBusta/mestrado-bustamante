#include "qhpoly.h"

#include "ric.h"
#include <QDebug>

typedef struct {
  int p1;
  int p2;

  QVector<int> points;
} PendingLine;

QHPoly::QHPoly()
{
}

QHPoly::QHPoly(const int &v0, const int &v1, const int &v2, const QVector<QVector3D> *vs, const QHPoly *parent)
  : vs_(vs),
    dead(false)
{
  //  qDebug() << "asd";
  face_v_.resize(3);
  face_v_[0] = v0;
  face_v_[1] = v1;
  face_v_[2] = v2;

  n_ = QVector3D::crossProduct(vs_->at(v1)-vs_->at(v0),vs_->at(v2)-vs_->at(v0)).normalized();
  c_ = (vs->at(v1)+vs->at(v0)+vs->at(v2))/3;

//  subset_v_.clear();

  //  if( NULL == parent ){
  for(int i=0;i<vs_->size();i++){
    if( QVector3D::dotProduct(n_,vs_->at(i)-vs_->at(face_v_[0])) > 0 ){
      subset_v_.push_back(i);
    }
  }

  qDebug() << "size" << subset_v_.size();
  //  }else{
  //    for(int i=0;i<vs_->size();i++){
  //      if( parent->subset_v_.contains(i) ){
  //        double dot = QVector3D::dotProduct(n_,vs_->at(i)-vs_->at(face_v_[0]));
  //        if(dot > 0){
  //          subset_v_.push_back(i);
  //        }else if( dot == 0){
  //          face_v_.push_back(i);
  //        }
  //      }
  //    }
  //  }
  //    qDebug() << v_.size();
}

QHPoly::QHPoly( const QHPoly &poly, const bool inverse )
  : vs_(poly.vs_),
    dead(false)
{
  face_v_ = poly.face_v_;
  n_ = poly.n_;
  c_ = poly.c_;
//  subset_v_.clear();
  subset_v_ = poly.subset_v_;
  qDebug() << "size" << subset_v_.size();
}

void QHPoly::CalcHull2D()
{
  if(face_v_.size()<=3) return;

  int minx=0, miny=0, minz=0, maxx=0, maxy=0, maxz=0;
  for(int i=0;i<face_v_.size();i++){
    if(vs_->at(minx).x() > vs_->at(i).x())  {
      minx = i;
    }

    if(vs_->at(maxx).x() < vs_->at(i).x())  {
      maxx = i;
    }

    if(vs_->at(miny).y() > vs_->at(i).y())  {
      miny = i;
    }

    if(vs_->at(maxy).y() < vs_->at(i).y())  {
      maxy = i;
    }

    if(vs_->at(minz).z() > vs_->at(i).z())  {
      minz = i;
    }

    if(vs_->at(maxz).z() < vs_->at(i).z())  {
      maxz = i;
    }
  }

  float difx = vs_->at(maxx).x()-vs_->at(minx).x();
  float dify = vs_->at(maxy).y()-vs_->at(miny).y();
  float difz = vs_->at(maxz).z()-vs_->at(minz).z();


  PendingLine p;
  //  p.p1 =
  if(difx > dify && difx > difz){
    p.p1 = minx;
    p.p2 = maxx;
  }else if(dify > difz){
    p.p1 = miny;
    p.p2 = maxy;
  }else{
    p.p1 = minz;
    p.p2 = maxz;
  }

}

bool QHPoly::GetRidge(const QHPoly &poly, QVector<int> &ridge/*,QVector<int> &not_ridge*/)
{
  for(int i=0;i<this->face_v_.size();i++){
    if(poly.face_v_.contains(face_v_[i]) && poly.face_v_.contains(face_v_[(i+1)%face_v_.size()])){
      ridge.push_back(face_v_[i]);
      ridge.push_back(face_v_[(i+1)%face_v_.size()]);
      qDebug() << "ridge!";
    }/*else{
      not_ridge.push_back(face_v_[i]);
      not_ridge.push_back(face_v_[(i+1)%face_v_.size()]);
    }*/
  }

  return false;
}
