#include "rendering/scenepointcloud.h"

ScenePointCloud::ScenePointCloud(const QString &name, const QString &owner, const double &spread, const QString &color)
  : SceneObject(name,owner,spread,color,false)
{
}

ScenePointCloud::~ScenePointCloud()
{
  ClearPoints();
}

void ScenePointCloud::DrawObject(const float &spread, const float &shrink, const bool user_color, const unsigned int current_frame) const
{
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  glDisable(GL_LIGHTING);
  glPointSize(6-5*shrink);
  glBegin(GL_POINTS);

  if(user_color){
    glColor3f(color_.redF(),color_.greenF(),color_.blueF());
  }

  foreach(QVector3D point, points_){
    Vertex(point+(point*spread));
  }

  glEnd();
  glPopAttrib();
}

void ScenePointCloud::Colorize()
{
  //  foreach(QVector3D *point, points_){
  //    int r,g,b;
  //  r = Ric::rand(256);
  //  g = Ric::rand(256);
  //  b = Ric::rand(256);
  //    point->SetColor(QColor(r,g,b));
  //  }
}

void ScenePointCloud::Delete()
{
  deleted_ = true;
  ClearPoints();
}

void ScenePointCloud::ClearPoints()
{
  points_.clear();
}
