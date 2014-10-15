#include "sceneobject.h"

//#include <QtOpenGL>
#ifdef _WIN32
#include <Windows.h>
#endif

#include <GL/gl.h>
#include <limits>

#include "programs/CG2/scene/triangleface.h"
#include "programs/CG2/scene/openglauxfunctions.h"
#include "programs/CG2/scene/objloader.h"

const float kMaxFloat = FLT_MAX;//std::numeric_limits<float>::max();
const float kMinFloat = -kMaxFloat;

SceneObject::SceneObject()
  : name("none"),
    bounding_worthy_(false)
{
}

SceneObject::SceneObject(const SceneObject *object, const Ric::Matrix4x4 *transform)
  : bounding_worthy_(object->bounding_worthy_),
    name(object->name)
{
  foreach(TriangleFace f,object->faces_){
    this->faces_.push_back(TriangleFace(f,transform));
  }
  foreach(TriangleFace f,object->bounding_volume_){
    this->bounding_volume_.push_back(TriangleFace(f,transform));
  }

  for(int i=0;i<object->child_objects_.size();i++){
    child_objects_.push_back(SceneObject(&object->child_objects_[i],transform));
  }
}

SceneObject::~SceneObject()
{

}

void SceneObject::move(Ric::Vector m)
{
  for(int i=0;i<faces_.size();i++) {
    faces_[i].move(m);
  }
  for(int i=0;i<child_objects_.size();i++){
    child_objects_[i].move(m);
  }
  GenerateBoundingVolumeRec();
}

void SceneObject::scale(double s)
{
  for(int i=0;i<faces_.size();i++) {
    faces_[i].scale(s);
  }
  for(int i=0;i<child_objects_.size();i++){
    child_objects_[i].scale(s);
  }
  GenerateBoundingVolumeRec();
}

void SceneObject::GlDraw(bool lighting,bool draw_bounding_box)
{
  //  qDebug() << "Drawing" << name;
  glPushAttrib(GL_ALL_ATTRIB_BITS);

  if(draw_bounding_box){
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glDisable(GL_LIGHTING);
    foreach(TriangleFace f,bounding_volume_){
      f.material().GlSet();
      glBegin(GL_TRIANGLES);
      Gl::Normal3f( f.n() );
      //      qDebug() << f.vt0();
      //      qDebug() << f.vn0();
      Gl::TexCoord( f.vt0() );
      //      Gl::Normal3f( f.vn0() );
      Gl::Vertex3f( f.v0() );
      Gl::TexCoord( f.vt1() );
      //      Gl::Normal3f( f.vn1() );
      Gl::Vertex3f( f.v1() );
      Gl::TexCoord( f.vt2() );
      //      Gl::Normal3f( f.vn2() );
      Gl::Vertex3f( f.v2() );
      glEnd();
    }
  }

  if(child_objects_.isEmpty()){
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    if(lighting){
      glEnable(GL_LIGHTING);
    }
    foreach(TriangleFace f,faces_){
      f.material().GlSet();
      if(lighting){
        glEnable(GL_LIGHTING);
      }
      glEnable(GL_TEXTURE_2D);
      glBegin(GL_TRIANGLES);
      Gl::Normal3f( f.n() );
      //      qDebug() << f.vt0();
      //      qDebug() << f.vn0();
      //      Gl::TexCoord( f.vt0() );
      Gl::Normal3f( f.vn0() );
      Gl::Vertex3f( f.v0() );
      //      Gl::TexCoord( f.vt1() );
      Gl::Normal3f( f.vn1() );
      Gl::Vertex3f( f.v1() );
      //      Gl::TexCoord( f.vt2() );
      Gl::Normal3f( f.vn2() );
      Gl::Vertex3f( f.v2() );
      glEnd();
      if(lighting){
        glDisable(GL_LIGHTING);
      }
      glBegin(GL_LINES);
      Gl::Vertex3f( f.v0() );
      //      qDebug() << "normal:" << f.vn0() << f.v0() << f.v0()+f.vn0();
      Gl::Vertex3f( f.v0()+f.vn0() );

      Gl::Vertex3f( f.v1() );
      Gl::Vertex3f( f.v1()+f.vn1() );
      Gl::Vertex3f( f.v2() );
      Gl::Vertex3f( f.v2()+f.vn2() );
      glEnd();
    }
  }else{
    for(int i=0;i<child_objects_.size();i++){
      child_objects_[i].GlDraw(lighting,draw_bounding_box);
    }
  }
  glPopAttrib();
}

void SceneObject::GenerateBoundingVolumeRec()
{
  QVector3D max_v = QVector3D(kMinFloat,kMinFloat,kMinFloat);
  QVector3D min_v = QVector3D(kMaxFloat,kMaxFloat,kMaxFloat);

  if(child_objects_.isEmpty()){
    foreach(TriangleFace f, faces_){
      ObjLoader::UpdateMaxAndMin(max_v,min_v,f.v0());
      ObjLoader::UpdateMaxAndMin(max_v,min_v,f.v1());
      ObjLoader::UpdateMaxAndMin(max_v,min_v,f.v2());
    }

    bounding_volume_.clear();
    bounding_volume_ += ObjLoader::CreateBoundingBox(min_v,max_v);
    //    qDebug() << bounding_volume_.size();
  }else{
    for(int i=0;i<child_objects_.size();i++){
      child_objects_[i].GenerateBoundingVolumeRec();
      foreach(TriangleFace f, child_objects_[i].bounding_volume_){
        ObjLoader::UpdateMaxAndMin(max_v,min_v,f.v0());
        ObjLoader::UpdateMaxAndMin(max_v,min_v,f.v1());
        ObjLoader::UpdateMaxAndMin(max_v,min_v,f.v2());
      }
    }
    bounding_volume_.clear();
    bounding_volume_ += ObjLoader::CreateBoundingBox(min_v,max_v);
    //    qDebug() << bounding_volume_.size();
  }

  bounding_worthy_ = (child_objects_.size()>=1 || bounding_volume_.size()<faces_.size());
}

SceneObject SceneObject::operator=(const SceneObject &o)
{
  name = o.name;

  faces_ = o.faces_;
  bounding_volume_ = o.bounding_volume_;
  center_ = o.center_;
  bounding_worthy_ = o.bounding_worthy_;
  material_ = o.material_;
  child_objects_ = o.child_objects_;

  return *this;
}
