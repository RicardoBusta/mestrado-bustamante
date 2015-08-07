#include "model.h"

#include <QtOpenGL/QGL>

Model::Model(): hidden_(false) {

}

void Model::Draw() const {
  if(hidden_){
    return;
  }
  glBegin(GL_TRIANGLES);
  foreach(const Vertex &v, mesh_){
    const QVector3D &p = v.position();
    const QVector3D &n = v.normal();
    const QVector3D &t = v.texcoord();
    glTexCoord2f(t.x(),t.y());
    glNormal3f(n.x(),n.y(),n.z());
    glVertex3f(p.x(),p.y(),p.z());
  }
  glEnd();
}

Model Model::Load(QString filename) {
  Model m;
  return m;
}

Model Model::LoadTriangle() {
  Model m;

  m.name_ = "Triangle";

  // Front Face
  m.mesh_.push_back(Vertex(QVector3D(-1,-1,0),QVector3D(0,0,1)));
  m.mesh_.push_back(Vertex(QVector3D(1,-1,0),QVector3D(0,0,1)));
  m.mesh_.push_back(Vertex(QVector3D(0,1,0),QVector3D(0,0,1)));

  // Back Face
  m.mesh_.push_back(Vertex(QVector3D(-1,-1,0),QVector3D(0,0,-1)));
  m.mesh_.push_back(Vertex(QVector3D(0,1,0),QVector3D(0,0,-1)));
  m.mesh_.push_back(Vertex(QVector3D(1,-1,0),QVector3D(0,0,-1)));

  return m;
}

Model Model::LoadCube() {
  Model m;

  m.name_ = "Cube";

  // Front Face
  m.mesh_.push_back(Vertex(QVector3D(-1,-1,+1),QVector3D(0,0,1),QVector2D(0,0)));
  m.mesh_.push_back(Vertex(QVector3D(+1,-1,+1),QVector3D(0,0,1),QVector2D(1,0)));
  m.mesh_.push_back(Vertex(QVector3D(+1,+1,+1),QVector3D(0,0,1),QVector2D(1,1)));
  m.mesh_.push_back(Vertex(QVector3D(-1,-1,+1),QVector3D(0,0,1),QVector2D(0,0)));
  m.mesh_.push_back(Vertex(QVector3D(+1,+1,+1),QVector3D(0,0,1),QVector2D(1,1)));
  m.mesh_.push_back(Vertex(QVector3D(-1,+1,+1),QVector3D(0,0,1),QVector2D(0,1)));
  // Back Face
  m.mesh_.push_back(Vertex(QVector3D(-1,-1,-1),QVector3D(0,0,-1),QVector2D(0,1)));
  m.mesh_.push_back(Vertex(QVector3D(+1,+1,-1),QVector3D(0,0,-1),QVector2D(1,0)));
  m.mesh_.push_back(Vertex(QVector3D(+1,-1,-1),QVector3D(0,0,-1),QVector2D(0,0)));
  m.mesh_.push_back(Vertex(QVector3D(-1,-1,-1),QVector3D(0,0,-1),QVector2D(0,1)));
  m.mesh_.push_back(Vertex(QVector3D(-1,+1,-1),QVector3D(0,0,-1),QVector2D(1,1)));
  m.mesh_.push_back(Vertex(QVector3D(+1,+1,-1),QVector3D(0,0,-1),QVector2D(1,0)));
  // Left Face
  m.mesh_.push_back(Vertex(QVector3D(-1,-1,-1),QVector3D(-1,0,0),QVector2D(0,0)));
  m.mesh_.push_back(Vertex(QVector3D(-1,-1,+1),QVector3D(-1,0,0),QVector2D(0,0)));
  m.mesh_.push_back(Vertex(QVector3D(-1,+1,+1),QVector3D(-1,0,0),QVector2D(0,0)));
  m.mesh_.push_back(Vertex(QVector3D(-1,-1,-1),QVector3D(-1,0,0),QVector2D(0,0)));
  m.mesh_.push_back(Vertex(QVector3D(-1,+1,+1),QVector3D(-1,0,0),QVector2D(0,0)));
  m.mesh_.push_back(Vertex(QVector3D(-1,+1,-1),QVector3D(-1,0,0),QVector2D(0,0)));
  // Right Face
  m.mesh_.push_back(Vertex(QVector3D(+1,-1,-1),QVector3D(1,0,0),QVector2D(0,0)));
  m.mesh_.push_back(Vertex(QVector3D(+1,+1,+1),QVector3D(1,0,0),QVector2D(0,0)));
  m.mesh_.push_back(Vertex(QVector3D(+1,-1,+1),QVector3D(1,0,0),QVector2D(0,0)));
  m.mesh_.push_back(Vertex(QVector3D(+1,-1,-1),QVector3D(1,0,0),QVector2D(0,0)));
  m.mesh_.push_back(Vertex(QVector3D(+1,+1,-1),QVector3D(1,0,0),QVector2D(0,0)));
  m.mesh_.push_back(Vertex(QVector3D(+1,+1,+1),QVector3D(1,0,0),QVector2D(0,0)));
  // Top Face
  m.mesh_.push_back(Vertex(QVector3D(-1,+1,-1),QVector3D(0,1,0),QVector2D(0,0)));
  m.mesh_.push_back(Vertex(QVector3D(-1,+1,+1),QVector3D(0,1,0),QVector2D(0,0)));
  m.mesh_.push_back(Vertex(QVector3D(+1,+1,+1),QVector3D(0,1,0),QVector2D(0,0)));
  m.mesh_.push_back(Vertex(QVector3D(-1,+1,-1),QVector3D(0,1,0),QVector2D(0,0)));
  m.mesh_.push_back(Vertex(QVector3D(+1,+1,+1),QVector3D(0,1,0),QVector2D(0,0)));
  m.mesh_.push_back(Vertex(QVector3D(+1,+1,-1),QVector3D(0,1,0),QVector2D(0,0)));
  // Bottom Face
  m.mesh_.push_back(Vertex(QVector3D(-1,-1,-1),QVector3D(0,-1,0),QVector2D(0,0)));
  m.mesh_.push_back(Vertex(QVector3D(+1,-1,+1),QVector3D(0,-1,0),QVector2D(0,0)));
  m.mesh_.push_back(Vertex(QVector3D(-1,-1,+1),QVector3D(0,-1,0),QVector2D(0,0)));
  m.mesh_.push_back(Vertex(QVector3D(-1,-1,-1),QVector3D(0,-1,0),QVector2D(0,0)));
  m.mesh_.push_back(Vertex(QVector3D(+1,-1,-1),QVector3D(0,-1,0),QVector2D(0,0)));
  m.mesh_.push_back(Vertex(QVector3D(+1,-1,+1),QVector3D(0,-1,0),QVector2D(0,0)));

  return m;
}

