#include "deltetra.h"

#include <QtOpenGL>

DelTetra::DelTetra()
{
  valid_ = false;
}

DelTetra::DelTetra(const QVector3D &v0,const QVector3D &v1,const QVector3D &v2,const QVector3D &v3, const QColor &color)
{
  v_.resize(4);
  n_.resize(4);

  center_ = (v0+v1+v2+v3)/4.0;

  v_[0] = v0;
  v_[1] = v1;
  v_[2] = v2;
  v_[3] = v3;

  n_[0] = QVector3D::crossProduct((v3-v1),(v2-v1)).normalized();
  n_[1] = QVector3D::crossProduct((v2-v0),(v3-v0)).normalized();
  n_[2] = QVector3D::crossProduct((v3-v0),(v1-v0)).normalized();
  n_[3] = QVector3D::crossProduct((v1-v0),(v2-v0)).normalized();

  color_ = color;

  valid_ = true;
}

void DelTetra::Draw(const float &spread, const float &shrink, const bool user_color) const
{
  if(!valid_) return;

  glPushMatrix();

  if(shrink>0){
    glTranslatef(center_.x(),center_.y(),center_.z());
    glScalef(1-shrink,1-shrink,1-shrink);
    glTranslatef(-center_.x(),-center_.y(),-center_.z());
  }

  if(spread>0){
    QVector3D s = center_*(spread);
    glTranslatef(s.x(),s.y(),s.z());
  }

  if(!user_color){
    glColor3f(color_.redF(),color_.greenF(),color_.blueF());
  }



  glBegin(GL_TRIANGLES);

  glNormal3f(n_[3].x(),n_[3].y(),n_[3].z());
  glVertex3f(v_[0].x(),v_[0].y(),v_[0].z());
  glVertex3f(v_[1].x(),v_[1].y(),v_[1].z());
  glVertex3f(v_[2].x(),v_[2].y(),v_[2].z());

  glNormal3f(n_[2].x(),n_[2].y(),n_[2].z());
  glVertex3f(v_[0].x(),v_[0].y(),v_[0].z());
  glVertex3f(v_[3].x(),v_[3].y(),v_[3].z());
  glVertex3f(v_[1].x(),v_[1].y(),v_[1].z());

  glNormal3f(n_[1].x(),n_[1].y(),n_[1].z());
  glVertex3f(v_[0].x(),v_[0].y(),v_[0].z());
  glVertex3f(v_[2].x(),v_[2].y(),v_[2].z());
  glVertex3f(v_[3].x(),v_[3].y(),v_[3].z());

  glNormal3f(n_[0].x(),n_[0].y(),n_[0].z());
  glVertex3f(v_[1].x(),v_[1].y(),v_[1].z());
  glVertex3f(v_[3].x(),v_[3].y(),v_[3].z());
  glVertex3f(v_[2].x(),v_[2].y(),v_[2].z());

  glEnd();

  glPopMatrix();
}

DelTetra DelTetra::operator=(const DelTetra &t)
{
  center_ = t.center_;
  color_ = t.color_;
  v_ = t.v_;
  n_ = t.n_;
  return *this;
}
