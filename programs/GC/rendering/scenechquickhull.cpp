#include "scenechquickhull.h"

SceneCHQuickHull::SceneCHQuickHull(const QString &name, const QString &owner, const double &spread, const QString &color):
  SceneObject(name,owner,spread,color,true),
  step_count_(0)
{
}

SceneCHQuickHull::~SceneCHQuickHull()
{
}

void SceneCHQuickHull::DrawObject(const float &spread, const float &shrink, const bool user_color, const unsigned int current_frame) const
{
  Q_UNUSED(shrink)
  Q_UNUSED(current_frame)
  if(points_.size() <= 0) return;

  glPushAttrib(GL_ALL_ATTRIB_BITS);


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

void SceneCHQuickHull::Clear()
{
  points_.clear();
}

void SceneCHQuickHull::Colorize()
{
}

void SceneCHQuickHull::Delete()
{
  deleted_ = true;
  Clear();
}

void SceneCHQuickHull::RunAlgorithm()
{
  //  while(StepAlgorithm()){
  if(StepAlgorithm()){
    qDebug() << QString("step quickhull: %1 (%2)").arg(step_count_).arg(name_);
  }
}

bool SceneCHQuickHull::StepAlgorithm()
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
                            horizon_ridge[i],
                            horizon_ridge[i+1],
                          max_dist_vert,
                          &points_,
                          NULL
                          ));
          todo_poly_list.pop_back();
        }
      }
    }


    horizon_ridge_faces.clear();
    horizon_ridge.clear();

    step_count_ = 3;
    return true;
  default:
    return false;
  }
}

float SceneCHQuickHull::DistanceSquaredBetweenPoints(const QVector3D &p1, const QVector3D &p2) const
{
  return (p2-p1).lengthSquared();
}

















