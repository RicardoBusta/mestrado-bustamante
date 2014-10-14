#include "triangleface.h"

#include "programs/CG2/scene/sceneobject.h"

#include <QImage>
#include <cmath>

#include "programs/CG2/structures/texturecontainer.h"

TriangleFace::TriangleFace()
{
}

TriangleFace::TriangleFace(const Ric::Vector &v0, const Ric::Vector &v1, const Ric::Vector &v2, const Ric::Material &material)
  : material_(material),
    v0_(v0),
    v1_(v1),
    v2_(v2),
    fc_((v0+v1+v2)/3),
    n_(((v1-v0)^(v2-v0)).Normalized()),
    area_(((v1-v0)^(v2-v0)).Length()),
    vertex_texture_coord(false),
    vertex_normal_(false)
{
  setNormals(n_,n_,n_);
}

TriangleFace::TriangleFace(const TriangleFace &f, const Ric::Matrix4x4 *transform)
{
  this->v0_ = Ric::Vector::transformv(f.v0_,*transform);
  this->v1_ = Ric::Vector::transformv(f.v1_,*transform);
  this->v2_ = Ric::Vector::transformv(f.v2_,*transform);
  this->fc_ = (v0_+v1_+v2_)/3;
  Ric::Vector normal = ((v1_-v0_)^(v2_-v0_));
  this->n_ = normal.Normalized();
  this->area_ = normal.Length();
  this->material_ = f.material();

  // change

//  this->vn0_ = f.vn0_;
//  this->vn1_ = f.vn1_;
//  this->vn2_ = f.vn2_;

//  Ric::Matrix4x4 t = transform->Inverted();
  this->vn0_ = (Ric::Vector::transformv(f.vn0_+f.v0_,*transform)-v0_).Normalized();
  this->vn1_ = (Ric::Vector::transformv(f.vn1_+f.v1_,*transform)-v1_).Normalized();
  this->vn2_ = (Ric::Vector::transformv(f.vn2_+f.v2_,*transform)-v2_).Normalized();

  if( vn0_ == vn1_ && vn1_ == vn2_ ){
    vertex_normal_ = true;
  }else{
    vertex_normal_ = false;
  }

  vt0_ = f.vt0_;
  vt1_ = f.vt1_;
  vt2_ = f.vt2_;

//  setTexCoords(f.vt0_,f.vt1_,f.vt2_);
  TBN_ = (*transform).Inverted().Transposed()*f.TBN_.Transposed();
}

void TriangleFace::setTexCoords(const Ric::Vector &vt0, const Ric::Vector &vt1, const Ric::Vector &vt2)
{
  vertex_texture_coord = true;

  vt0_ = vt0;
  vt1_ = vt1;
  vt2_ = vt2;

  // http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-13-normal-mapping/
  // Edges of the triangle
  Ric::Vector deltaPos1 = v1_ - v0_;
  Ric::Vector deltaPos2 = v2_ - v0_;
  Ric::Vector deltaUV1 = vt1_ - vt0_;
  Ric::Vector deltaUV2 = vt2_ - vt0_;

  float r = 1.0f / (deltaUV1.x() * deltaUV2.y() - deltaUV1.y() * deltaUV2.x());
  tangent_ = ( deltaPos1 * deltaUV2.y() - deltaPos2 * deltaUV1.y() )*r;
  bitangent_ = ( deltaPos2 * deltaUV1.x() - deltaPos1 * deltaUV2.x() )*r;

  TBN_ = Ric::Matrix4x4(tangent_,bitangent_,n_);
}

void TriangleFace::setNormals(const Ric::Vector &vn0, const Ric::Vector &vn1, const Ric::Vector &vn2)
{
  vn0_ = vn0;
  vn1_ = vn1;
  vn2_ = vn2;

  if( vn0_ == vn1_ && vn1_ == vn2_ ){
    vertex_normal_ = true;
  }else{
    vertex_normal_ = false;
  }
}


Ric::Vector TriangleFace::vt0() const
{
  return vt0_;
}

Ric::Vector TriangleFace::vt1() const
{
  return vt1_;
}

Ric::Vector TriangleFace::vt2() const
{
  return vt2_;
}

Ric::Vector TriangleFace::vn0() const
{
  return vn0_;
}

Ric::Vector TriangleFace::vn1() const
{
  return vn1_;
}

Ric::Vector TriangleFace::vn2() const
{
  return vn2_;
}
Ric::Material TriangleFace::material() const
{
  return material_;
}

void TriangleFace::scale(double s)
{
  v0_ = v0_ * s;
  v1_ = v1_ * s;
  v2_ = v2_ * s;
  fc_ = (v0_+v1_+v2_)/3;
  n_ = ((v1_-v0_)^(v2_-v0_)).Normalized();
}

void TriangleFace::move(Ric::Vector m)
{
  v0_ += m;
  v1_ += m;
  v2_ += m;
  fc_ += m;
  n_ += m;
}


void TriangleFace::setMaterial(const Ric::Material &material)
{
  material_ = material;
}
Ric::Vector TriangleFace::v0() const
{
  return v0_;
}

void TriangleFace::setV0(const Ric::Vector &v0)
{
  v0_ = v0;
}
Ric::Vector TriangleFace::v1() const
{
  return v1_;
}

void TriangleFace::setV1(const Ric::Vector &value)
{
  v1_ = value;
}
Ric::Vector TriangleFace::v2() const
{
  return v2_;
}

void TriangleFace::setV2(const Ric::Vector &value)
{
  v2_ = value;
}
Ric::Vector TriangleFace::fc() const
{
  return fc_;
}

void TriangleFace::setFc(const Ric::Vector &value)
{
  fc_ = value;
}


Ric::Vector TriangleFace::n() const
{
  return n_;
}

void TriangleFace::setN(const Ric::Vector &n)
{
  n_ = n;
}

bool TriangleFace::vertex_normal() const
{
  return vertex_normal_;
}

Ric::Vector TriangleFace::n_b(const Ric::Vector &b) const
{
  Ric::Vector output;

//  qDebug() << b.x() << b.y()<< b.z() << (b.x()+b.y()+b.z());
//  if(material().has_normal_map()){
//    output = Ric::Vector::transformv(Ric::Vector(0,0,1),TBN_);
//  }else{
    output = ((vn0_*b.x())+(vn1_*b.y())+(vn2_*b.z())).Normalized();
//  }
//  output = vn0_;

  return output;
}

Ric::Color TriangleFace::t_b(const Ric::Vector &b) const
{
    Ric::Color output;

    bool interp = true;

    const QImage *texture = (TextureContainer::instance()->get( QString::fromStdString(material().GetDifTexture())) );

    if(texture != NULL && material().has_texture() && !texture->isNull()){
      Ric::Vector coord = ((vt0_*b.x()) + (vt1_ * b.y()) + ( vt2_ * b.z() ));

      if(interp){
        int cx = ceil( coord.x() * (texture->width()-1) );
        int fx = floor( coord.x() * (texture->width()-1) );
        int cy = ceil( coord.y() * (texture->height()-1) );
        int fy = floor( coord.y() * (texture->height()-1) );
        float difx = (cx-fx);
        float dify = (cy-fy);
        output = texture->pixel( (difx)*fx + (1-difx)*cx , texture->height() - ((dify)*fy + (1-dify)*cy) );
      }else{
        output = texture->pixel( (int)(coord.x()*texture->width())%texture->width(), texture->height() - (int)(coord.y()*texture->height())%texture->height() );
      }
    }else{
//      qDebug() << "image null";
      output = material().diffuse();
    }

    return output;
}

double TriangleFace::area() const
{
  return area_;
}

//Ric::Material TriangleFace::material()
//{
//  return object_->material_;
//}
