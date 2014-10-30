#include "scenetetradelaunay.h"

SceneTetraDelaunay::SceneTetraDelaunay(const QString &name, const QString &owner, const double &spread, const QString &color)
  : SceneObject(name,owner,spread,color,true),
    step_count_(0)
{
  marked_points_.clear();
}

SceneTetraDelaunay::~SceneTetraDelaunay()
{

}

void SceneTetraDelaunay::DrawObject(const float &spread, const float &shrink, const bool user_color, const unsigned int current_frame) const
{
  Q_UNUSED(shrink)
  Q_UNUSED(current_frame)
  if(points_.size() <= 0) return;

  glPushAttrib(GL_ALL_ATTRIB_BITS);

  foreach(DelTetra tetrahedron, tetra_){
    tetrahedron.Draw(spread,shrink,user_color);
  }

  glDisable(GL_LIGHTING);
  //glPointSize(6-5*shrink);
  //  if(user_color){
  //    glColor3f(color_.redF(),color_.greenF(),color_.blueF());
  //  }
  //  glPointSize(6);
  //  glBegin(GL_POINTS);
  //  foreach(QVector3D point, points_){
  //    Vertex(point+(point*spread));
  //  }
  //  glEnd();
  glColor3f(1,0,0);
  glPointSize(11-10*shrink);
  glBegin(GL_POINTS);
  foreach(int index, v_max){
    Vertex( points_[index]+(points_[index]*spread) );
  }
  glEnd();

  glColor3f(0,0,1);
  glPointSize(15-14*shrink);
  glBegin(GL_POINTS);
  foreach(int index, v_3_sel){
    Vertex( points_[index]+(points_[index]*spread) );
  }
  glEnd();

  glEnable(GL_LIGHTING);


  for(int i=0;i<todo_poly_list.size();i++){
    const QHPoly &poly = todo_poly_list[i];

    if(poly.dead) continue;

    if(horizon_ridge_faces.contains(i)){
      glColor3f(0,0,1);
    }else if(i==0){
      glColor3f(1,0,0);
    }else{
      glColor3f(1,1,1);
    }
    Normal( poly.n_ );
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0; i<poly.face_v_.size(); i++){
      Vertex( points_[poly.face_v_[i]]+((poly.c_+poly.n_)*spread) );
    }
    glEnd();
    Normal( -poly.n_ );
    glBegin(GL_TRIANGLE_FAN);
    for(int i=poly.face_v_.size()-1; i>=0; i--){
      Vertex( points_[poly.face_v_[i]]+((poly.c_+poly.n_)*spread) );
    }
    glEnd();
    glColor3f(1,0,0);
    glBegin(GL_LINES);
    Vertex( poly.c_ + ((poly.c_+poly.n_)*spread));
    Vertex( poly.c_+poly.n_ + ((poly.c_+poly.n_)*spread) );
    glEnd();
  }

  foreach(QHPoly poly, poly_){
    if(user_color){
      glColor3f(color_.redF(),color_.greenF(),color_.blueF());
    }
    Normal( poly.n_ );
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0; i<poly.face_v_.size(); i++){
      Vertex( points_[poly.face_v_[i]]+((poly.c_+poly.n_)*spread) );
    }
    glEnd();
    Normal( -poly.n_ );
    glBegin(GL_TRIANGLE_FAN);
    for(int i=poly.face_v_.size()-1; i>=0; i--){
      Vertex( points_[poly.face_v_[i]]+((poly.c_+poly.n_)*spread) );
    }
    glEnd();
    glColor3f(1,0,0);
    glBegin(GL_LINES);
    Vertex( poly.c_ + ((poly.c_+poly.n_)*spread));
    Vertex( poly.c_+poly.n_ + ((poly.c_+poly.n_)*spread) );
    glEnd();
  }

  glDisable(GL_LIGHTING);
  if(todo_poly_list.size()>0){
    glPointSize(11-10*shrink);
    glBegin(GL_POINTS);
    for(int i=0;i<todo_poly_list.first().subset_v_.size();i++){
      //foreach(int index, todo_poly_list.first().subset_v_){
      int index = todo_poly_list.first().subset_v_.at(i);
      if(index == max_dist_vert){
        glColor3f(0,1,0);
      }else{
        glColor3f(1,0,0);
      }
      Vertex( points_[index]+(points_[index]*spread) );
    }
    glEnd();
  }

  glColor3f(0,1,0);
  glLineWidth(5-4*shrink);
  glBegin(GL_LINES);
  foreach(int index, horizon_ridge){
    Vertex(points_[index]+(points_[index]*spread));
  }
  glEnd();

  //  glColor3f(1,0,0);
  //  glLineWidth(5);
  //  glBegin(GL_LINES);
  //    foreach(int index, horizon_not_ridge){
  //      Vertex(points_[index]);
  //    }
  //  glEnd();

  glPopAttrib();
}

void SceneTetraDelaunay::Clear()
{
  points_.clear();
}

void SceneTetraDelaunay::Colorize()
{
}

void SceneTetraDelaunay::Delete()
{
  deleted_ = true;
  Clear();
}

void SceneTetraDelaunay::RunAlgorithm()
{
  //  while(StepAlgorithm()){
  while(step_count_<100 && StepAlgorithm()){
    qDebug() << QString("step first_face: %1 (%2)").arg(step_count_).arg(name_);
  }

  if(step_count_ >= 100 && StepAlgorithm()){
    qDebug() << QString("step delaunay: %1 (%2)").arg(step_count_).arg(name_);
  }
}

#include "geometry.h"
#include "rendering/qhpoly.h"
#include <QVector3D>

bool SceneTetraDelaunay::StepAlgorithm()
{
  QHPoly p;
  float d;
  int min_dist_vert;
  float min_dist;

  if(step_count_ < 100){
    return FindFirstFace();
  }

  switch(step_count_){
  case 100:
    //    dead_points_.fill(false,points_.size());
    step_count_ = 101;

  case 101:
    min_dist_vert = -1;
    min_dist = 99999;

    qDebug() << "poly_size" << poly_.size();

    if(poly_.empty() || poly_.first().vs_->size() < 3){
      step_count_ = 200;
      return false;
    }

    p = poly_.first();
    //    dead_points_[p.face_v_[0]] = true;
    //    dead_points_[p.face_v_[1]] = true;
    //    dead_points_[p.face_v_[2]] = true;

    for(int i=0;i<points_.size();i++){
      //      if(dead_points_[i] == false){
      d = OrientedSolidAngle(points_[i],p);/*points_[i].distanceToPlane(points_[p.face_v_.at(0)],points_[p.face_v_.at(1)],points_[p.face_v_.at(2)]);*/
      qDebug() << "d" << d;
      if(d <= 0) continue;
      //        d = (d<0?-1.0:1.0)/(d*d);
      if(d<min_dist){
        min_dist = d;
        min_dist_vert = i;
      }
      //      }
    }

    qDebug() << min_dist_vert;

    if(min_dist_vert != -1){
      //      dead_points_[p.face_v_[max_dist_vert]] = true;
      poly_.push_back(QHPoly(p.face_v_.at(0),p.face_v_.at(1),min_dist_vert,&points_,&p));
      poly_.push_back(QHPoly(p.face_v_.at(1),p.face_v_.at(2),min_dist_vert,&points_,&p));
      poly_.push_back(QHPoly(p.face_v_.at(2),p.face_v_.at(0),min_dist_vert,&points_,&p));
      tetra_.push_back(DelTetra(points_[p.face_v_.at(0)],points_[p.face_v_.at(2)],points_[p.face_v_.at(1)],points_[min_dist_vert],color_));
      poly_.pop_front();
    }else{
      poly_.pop_front();
    }

    return true;
  default:
    return false;
  }

  return true;
}
bool SceneTetraDelaunay::FindFirstFace()
{
  // case 1
  double max_dist;
  int max_i, max_j, max_k;
  // case 2
  QHPoly *pcw, *pccw;

  //  horizon_not_ridge.clear();

  switch(step_count_){
  case 0:
    max_dist_vert = -1;
    // build the 6 min and max points
    if(points_.size()<1){
      return false;
    }

    v_max.fill(0,6);

    for(int i = 0; i<points_.size(); i++){
      // Min X
      if( points_[i].x() < points_[v_max[0]].x() ){
        v_max[0] = i;
      }

      // Max X
      if( points_[i].x() > points_[v_max[1]].x() ){
        v_max[1] = i;
      }

      // Min X
      if( points_[i].y() < points_[v_max[2]].y() ){
        v_max[2] = i;
      }

      // Max X
      if( points_[i].y() > points_[v_max[3]].y() ){
        v_max[3] = i;
      }

      // Min X
      if( points_[i].z() < points_[v_max[4]].z() ){
        v_max[4] = i;
      }

      // Max X
      if( points_[i].z() > points_[v_max[5]].z() ){
        v_max[5] = i;
      }
    }
    step_count_=1;
    return true;
  case 1:
    // find the 3 starting points of the set to begin the hull creation
    v_3_sel.resize(3);

    // Of the 6 extreme points, two points with the biggest distance.
    max_dist = 0;
    max_i = 0;
    max_j = 0;
    for(int i=0;i<6;i++){
      for(int j=i+1;j<6;j++){
        double new_dist = DistanceSquaredBetweenPoints(points_[v_max[i]],points_[v_max[j]]);
        if( new_dist > max_dist ){
          max_dist = new_dist;
          max_i = i;
          max_j = j;
        }
      }
    }

    v_3_sel[0] = v_max[max_i];
    v_3_sel[1] = v_max[max_j];

    // Get the 3rd point to generate the two first triangles.
    max_dist = 0;
    max_k = 0;
    for(int k=0;k<6;k++){
      if(k!=max_i && k!=max_j){
        double new_dist = points_[v_max[k]].distanceToLine(points_[v_3_sel[0]],points_[v_3_sel[1]]-points_[v_3_sel[0]]);
        if( new_dist > max_dist ){
          max_dist = new_dist;
          max_k = k;
        }
      }
    }
    v_3_sel[2] = v_max[max_k];
    step_count_=2;
    return true;
  case 2:
    // find out 3 sets: the points on both sides, and coplanar points.
    // points on each side will be added to the respective polygon list, and the coplanar will be considered for the 2D convex hull algorithm to find the starting face.

    todo_poly_list.push_back(QHPoly(v_3_sel[0],v_3_sel[1],v_3_sel[2],&points_,NULL));
    //pcw = &todo_poly_list.last();
    //pcw->debug_color = QColor(255,0,0);
    todo_poly_list.last().debug_color = QColor(255,0,0);

    for(int i=0;i<points_.size();i++){
      float f = points_[i].distanceToPlane(points_[v_3_sel[0]],points_[v_3_sel[1]],points_[v_3_sel[2]]);
      if(f>=0){
        todo_poly_list.last().subset_v_.push_back(i);
      }
    }

    todo_poly_list.push_back(QHPoly(v_3_sel[0],v_3_sel[2],v_3_sel[1],&points_,NULL));
    //pccw = &todo_poly_list.last();
    //pccw->debug_color = QColor(0,0,255);

    todo_poly_list.last().debug_color = QColor(0,0,255);

    for(int i=0;i<points_.size();i++){
      float f = points_[i].distanceToPlane(points_[v_3_sel[0]],points_[v_3_sel[1]],points_[v_3_sel[2]]);
      if(f>=0){
        todo_poly_list.last().subset_v_.push_back(i);
      }
    }

    //    for(int i=0;i<points_.size();i++){
    //      float f = points_[i].distanceToPlane(points_[v_3_sel[0]],points_[v_3_sel[1]],points_[v_3_sel[2]]);
    //      if(f>=0){
    //        pcw->subset_v_.push_back(i);
    //      }
    //      if(f<=0){
    //        pccw->subset_v_.push_back(i);
    //      }
    //      //      if(f==0){
    //      //        pcw->face_v_.push_back(i);
    //      //        pccw->face_v_.push_back(i);
    //      //      }
    //    }
    //    qDebug() << "pcw subset" << pcw->subset_v_.size();
    //    qDebug() << "pccw subset" << pccw->subset_v_.size();

    //    pcw->CalcHull2D();

    v_3_sel.clear();
    v_max.clear();

    step_count_=3;
    return true;
  case 3:
    if(todo_poly_list.size()>0){
      max_dist_vert = -1;
      qDebug() << todo_poly_list.first().subset_v_.size();
      if(todo_poly_list.first().subset_v_.size() <= 0){
        poly_.push_back(QHPoly(todo_poly_list.first(),false));
        todo_poly_list.pop_front();
      }else{
        // Find the farthest point from the plane and figure out which planes are from the horizon ridge
        double max_dist = 0;
        for(int i=0;i<todo_poly_list.first().subset_v_.size();i++){
          double new_dist = (points_[todo_poly_list.first().subset_v_[i]].distanceToPlane(points_[todo_poly_list.first().face_v_[0]],points_[todo_poly_list.first().face_v_[1]],points_[todo_poly_list.first().face_v_[2]]));
          if(new_dist > max_dist){
            max_dist = new_dist;
            max_dist_vert = todo_poly_list.first().subset_v_[i];
          }
        }

        // Will detect the horizon ridge faces
        if(max_dist_vert!=-1){
          for(int i=0;i<todo_poly_list.size();i++){
            double dist = points_[max_dist_vert].distanceToPlane(todo_poly_list[i].c_,todo_poly_list[i].n_);
            if(0 < dist){
              qDebug() << i << dist;
              horizon_ridge_faces.push_back(i);
            }
          }

          // Will try to find the polygon that makes the ridge. Hardest part will be orientation.
          for(int i=0;i<horizon_ridge_faces.size();i++){
            QHPoly &poly1 = todo_poly_list[horizon_ridge_faces[i]];

            for(int j=0;j<todo_poly_list.size();j++){
              if(horizon_ridge_faces.contains(j)) continue;

              QHPoly &poly2 = todo_poly_list[j];

              poly1.GetRidge(poly2,horizon_ridge);
            }
            for(int j=0;j<poly_.size();j++){
              QHPoly &poly2 = poly_[j];

              poly1.GetRidge(poly2,horizon_ridge);
            }
          }

          // Ok.
        }
      }
      step_count_=4;
    }else{
      step_count_=100;
    }

    return true;
  case 4:
    if(max_dist_vert!=-1){
      //       If does, build the next 3 iteration triangles and remove self.
      //      for(int i=0;i<todo_poly_list.first().face_v_.size();i++){
      //        qDebug() << "adding face" << todo_poly_list.first().face_v_.size();
      //        todo_poly_list.push_back(QHPoly(
      //                                   todo_poly_list.first().face_v_[i],
      //                                   todo_poly_list.first().face_v_[(i+1)%todo_poly_list.first().face_v_.size()],
      //                                 max_dist_vert,
      //                                 &points_,
      //                                 &todo_poly_list.first()));
      //      }
      for(int i=0;i<horizon_ridge_faces.size();i++){
        todo_poly_list[horizon_ridge_faces[i]].dead = true;
      }

      for(int i=0;i<todo_poly_list.size();){
        if(todo_poly_list[i].dead){
          todo_poly_list.removeAt(i);
        }else{
          i++;
        }
      }

      for(int i=0;i<horizon_ridge.size();i+=2){
        todo_poly_list.push_back(QHPoly(
                                   horizon_ridge[i],
                                   horizon_ridge[i+1],
                                 max_dist_vert,
                                 &points_,
                                 (todo_poly_list.isEmpty())?NULL:(&todo_poly_list.first())
                                                            ));
        if(todo_poly_list.last().subset_v_.isEmpty()){
          poly_.push_back(QHPoly(
                            horizon_ridge[i+1],
                          horizon_ridge[i],
                          max_dist_vert,
                          &points_,
                          NULL
                          ));
          todo_poly_list.clear();
          horizon_ridge_faces.clear();
          horizon_ridge.clear();
          step_count_ = 100;
          return true;
        }
      }
    }


    horizon_ridge_faces.clear();
    horizon_ridge.clear();

    step_count_ = 3;
    return true;
  default:
    return true;
  }
}

double SceneTetraDelaunay::OrientedSolidAngle(const QVector3D &p, const QHPoly &face)
{
  QVector3D p0 = face.vs_->at(face.face_v_[0]);
  QVector3D p1 = face.vs_->at(face.face_v_[1]);
  QVector3D p2 = face.vs_->at(face.face_v_[2]);

  QVector3D a(p0 - p);
  QVector3D b(p1 - p);
  QVector3D c(p2 - p);

  double al = a.length();
  double bl = b.length();
  double cl = c.length();

  double d = al*bl*cl + QVector3D::dotProduct(a,b)*cl + QVector3D::dotProduct(b,c)*al + QVector3D::dotProduct(c,a)*bl;

  if( d < 0.0001 && d > -0.0001 ){
    return 0.0;
  }

  double num = a.QVector3D::dotProduct(a,QVector3D::crossProduct(c,b));
  double ang = 2.0*atan2(num,d);

  if(ang < 0.0001 && ang > -0.0001){
    ang = 0.0;
  }

  QVector3D n = (QVector3D::crossProduct((p1-p0),(p2-p0))).normalized();
  QVector3D v = (p-p0).normalized();

  bool an = (QVector3D::dotProduct(n,v) < 0.0001);

  ang = an?
        ((ang < 0.0) ?  2.0*M_PI + ang : ang):
        ((ang > 0.0) ? -2.0*M_PI + ang : ang);

  return -ang;
}

bool SceneTetraDelaunay::Intersection(const QHPoly &poly, const QVector3D &v1, const QVector3D &v2)
{
  QVector3D p0 = poly.vs_->at(poly.face_v_[0]);
  QVector3D p1 = poly.vs_->at(poly.face_v_[1]);
  QVector3D p2 = poly.vs_->at(poly.face_v_[2]);

  QVector3D d = QVector3D(v2-v1);
  double dnorm = d.length();
  d.normalize();
  QVector3D e1 = QVector3D(p1-p0);
  QVector3D e2 = QVector3D(p2-p0);

  QVector3D p = QVector3D::crossProduct(d,e2);
  double m = QVector3D::dotProduct(p,e1);

  if(fabs(m) < 0.0001){
    return false;
  }

  m = 1.0/m;

  QVector3D s(v1 - p0);

  double u = m*QVector3D::dotProduct(s,p);

  if ((u < 0.0001) || (u > (1.0 - 0.0001)))
  {
    return false;
  }

  QVector3D q = QVector3D::crossProduct(s,e1);

  double v = m*QVector3D::dotProduct(d,q);

  if ((v < 0.0001) || (v > (1.0 - 0.0001)))
  {
    return false;
  }

  if ((u + v) > (1.0 - 0.0001))
  {
    return false;
  }

  double t = m*QVector3D::dotProduct(e2,q);

  if ((t < 0.0001) || (t > dnorm - 0.0001))
  {
    return false;
  }

  return true;
}

bool SceneTetraDelaunay::Intersection(const QHPoly &poly, const QHPoly &face)
{
  bool res = Intersection(poly,face.vs_->at(face.face_v_[0]),face.vs_->at(face.face_v_[1])) ||
  Intersection(poly,face.vs_->at(face.face_v_[1]),face.vs_->at(face.face_v_[2])) ||
  Intersection(poly,face.vs_->at(face.face_v_[2]),face.vs_->at(face.face_v_[0]))||

  Intersection(face,poly.vs_->at(poly.face_v_[0]),poly.vs_->at(poly.face_v_[1])) ||
  Intersection(face,poly.vs_->at(poly.face_v_[1]),poly.vs_->at(poly.face_v_[2])) ||
  Intersection(face,poly.vs_->at(poly.face_v_[2]),poly.vs_->at(poly.face_v_[0]));

  return res;
}

bool SceneTetraDelaunay::Intersection(const QHPoly &poly, const DelTetra &tetra)
{
  QHPoly();
  return false;
}

float SceneTetraDelaunay::DistanceSquaredBetweenPoints(const QVector3D &p1, const QVector3D &p2) const
{
  return (p2-p1).lengthSquared();
}
