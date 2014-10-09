#include "ray.h"

#include "scene/scene.h"

#include <QDebug>
#include <QtOpenGL>

#include "structures.h"
#include "scene/triangleface.h"

#include "structures/texturecontainer.h"

QImage texture;

Ray::Ray()
  : hit_(false),
    near_length_(0),
    far_length_(0),
    default_color_(0x00000000),
    color_(0x00000000)
{
  //  qDebug() << "loading texture:";
  //  qDebug() << (texture.load("://models/cubes.png"));
  //  qDebug() << !texture.isNull();
}

Ray::Ray(Ric::Vector o, Ric::Vector d, double far_length, double near_length, Ric::Color c)
  : hit_(false),
    near_length_(near_length),
    far_length_(far_length),
    o_(o),
    d_(d),
    default_color_(c),
    color_(c)
{}

Ray::~Ray()
{
  //  if(texture != NULL){
  //    delete texture;
  //  }
}

const TriangleFace *Ray::cast(const Scene *s)
{
  hit_ = false;
  t_ = far_length_;
  const TriangleFace *hit_face = NULL;
  QVector<SceneObject>::const_iterator transformed_object_it;

  for(transformed_object_it = s->transformed_object_.begin();transformed_object_it!=s->transformed_object_.end();transformed_object_it++){
    const TriangleFace *hit = cast(&(*transformed_object_it));
    if(hit != NULL){
      hit_face = hit;
    }
  }
  return hit_face;
}

const TriangleFace *Ray::cast(const SceneObject *o)
{
  // TODO fazer o cast com um scene object. Caso o objeto seja composto, chamar recursivamente para cada sub objeto caso seja true para a "bounding area".
  const TriangleFace *hit_face = NULL;

  //  qDebug() << "cast";
  if(o->bounding_worthy_){
    //    qDebug() << "bounding worthy";
    bool hit = false;
    QVector<TriangleFace>::const_iterator bounding_faces_it;
    for(bounding_faces_it=o->bounding_volume_.begin();bounding_faces_it!=o->bounding_volume_.end();bounding_faces_it++){
      const TriangleFace &f = (*bounding_faces_it);
      double vD = f.n()*d_;
      if(vD != 0){
        float vO = -(f.n()*o_)+(f.n()*f.v0());
        float new_t = vO/vD;
        if(new_t<t_ && new_t>near_length_){
          Ric::Vector new_p = (o_+(d_*new_t));
          Ric::Vector d1 = (f.v1()-f.v0())^(new_p-f.v0());
          Ric::Vector d2 = (f.v2()-f.v1())^(new_p-f.v1());
          Ric::Vector d3 = (f.v0()-f.v2())^(new_p-f.v2());

          float l1 = d1*f.n();
          float l2 = d2*f.n();
          float l3 = d3*f.n();
          if((l1 >= 0) && (l2 >= 0) && (l3 >= 0)){
            hit = true;

            // DEBUG, draw boundingbox
            //            hit_face = &f;
            //            hit_ = true;
            //            t_ = new_t;
            //            p_ = new_p;
            //            n_ = f.n();
            //            return hit_face;

            break;
          }
        }
      }
    }

    if( false == hit ){
      return NULL;
    }
  }
  //  qDebug() << "break";

  for(int i=0;i<o->child_objects_.size();i++){
    const TriangleFace *hit = NULL;
    hit = cast(&(o->child_objects_[i]));
    if(hit != NULL){
      hit_face = hit;
    }
  }

  QVector<TriangleFace>::const_iterator faces_it;
  for(faces_it=o->faces_.begin();faces_it!=o->faces_.end();faces_it++){
    const TriangleFace &f = (*faces_it);
    double vD = f.n()*d_;

    if(vD < 0 || !o->child_objects_.isEmpty()){
      float vO = -(f.n()*o_)+(f.n()*f.v0());
      float new_t = vO/vD;
      if(new_t<t_ && new_t>near_length_){
        Ric::Vector new_p = (o_+(d_*new_t));
        Ric::Vector d1 = (f.v1()-f.v0())^(new_p-f.v0());
        Ric::Vector d2 = (f.v2()-f.v1())^(new_p-f.v1());
        Ric::Vector d3 = (f.v0()-f.v2())^(new_p-f.v2());

        float l1 = d1*f.n();
        float l2 = d2*f.n();
        float l3 = d3*f.n();

        if((l1 >= 0) && (l2 >= 0) && (l3 >= 0)){
          hit_face = &f;
          hit_ = true;
          t_ = new_t;
          p_ = new_p;
          n_ = f.n();
          b_ = Ric::Vector(l2/f.area(),l3/f.area(),l1/f.area());
          return hit_face;
        }
      }
    }
  }
  return hit_face;
}

const TriangleFace *Ray::envCast(const Scene *s)
{
  hit_ = false;
  t_ = far_length_;
  const TriangleFace *hit_face = NULL;

  const TriangleFace *hit = cast(&s->environment);
  if(hit != NULL){
    hit_face = hit;
  }
  return hit_face;
}

bool Ray::shadowCast(const Scene *s)
{
  hit_ = false;
  t_ = far_length_;
  QVector<SceneObject>::const_iterator transformed_object_it;
  for(transformed_object_it = s->transformed_object_.begin();transformed_object_it!=s->transformed_object_.end();transformed_object_it++){
    bool hit = shadowCast(&(*transformed_object_it));
    if(hit){
      hit_ = true;
      return true;
    }
  }
  return false;
}

bool Ray::shadowCast(const SceneObject *o)
{
  // TODO fazer o cast com um scene object. Caso o objeto seja composto, chamar recursivamente para cada sub objeto caso seja true para a "bounding area".
  //  const TriangleFace *hit_face = NULL;

  //  qDebug() << "cast";

  //  bool bounding_hit = false;

  //  QVector<TriangleFace>::const_iterator bounding_faces_it;
  //  for(bounding_faces_it=o->bounding_volume_.begin();bounding_faces_it!=o->bounding_volume_.end();bounding_faces_it++){
  //    const TriangleFace &f = (*bounding_faces_it);
  //    double vD = f.n()*d_;

  //    if(vD != 0){
  //      float vO = -(f.n()*o_)+(f.n()*f.v0());
  //      float new_t = vO/vD;
  //      if(new_t<t_ && new_t>near_length_){
  //        Ric::Vector new_p = (o_+(d_*new_t));
  //        Ric::Vector d1 = (f.v1()-f.v0())^(new_p-f.v0());
  //        Ric::Vector d2 = (f.v2()-f.v1())^(new_p-f.v1());
  //        Ric::Vector d3 = (f.v0()-f.v2())^(new_p-f.v2());

  //        float l1 = d1*f.n();
  //        float l2 = d2*f.n();
  //        float l3 = d3*f.n();

  //        if((l1 >= 0) && (l2 >= 0) && (l3 >= 0)){
  ////          hit_face = &f;
  ////          hit_ = true;
  //          bounding_hit = true;
  //          break;
  //        }
  //      }
  //    }
  //  }

  //  if(!bounding_hit) return false;

  for(int i=0;i<o->child_objects_.size();i++){
    bool hit = false;
    hit = shadowCast(&(o->child_objects_[i]));
    if(hit){
      hit_ = true;
      return true;
    }
  }

  QVector<TriangleFace>::const_iterator faces_it;
  for(faces_it=o->faces_.begin();faces_it!=o->faces_.end();faces_it++){
    const TriangleFace &f = (*faces_it);
    double vD = f.n()*d_;

    if(vD != 0 || !o->child_objects_.isEmpty()){
      float vO = -(f.n()*o_)+(f.n()*f.v0());
      float new_t = vO/vD;
      if(new_t<t_ && new_t>near_length_){
        Ric::Vector new_p = (o_+(d_*new_t));
        Ric::Vector d1 = (f.v1()-f.v0())^(new_p-f.v0());
        Ric::Vector d2 = (f.v2()-f.v1())^(new_p-f.v1());
        Ric::Vector d3 = (f.v0()-f.v2())^(new_p-f.v2());

        float l1 = d1*f.n();
        float l2 = d2*f.n();
        float l3 = d3*f.n();

        if((l1 >= 0) && (l2 >= 0) && (l3 >= 0)){
          //          hit_face = &f;
          hit_ = true;
          return true;
        }
      }
    }
  }
  return false;
}

void Ray::calc(const TriangleFace *f, const Scene *scene, const unsigned int &level, const bool &adv_light)
{
  color_ = default_color_;

  if(NULL == f) return;

  if(!adv_light){
    color_ = (f->material().diffuse());
    return;
  }

  v_ = (o_-p_).Normalized();

  Ric::Vector n_b;
  //  if(f->vertex_normal()){
  n_b = f->n_b(b_);
  //  }else{
  //    n_b = n_;
  //  }
  //  n_b = f->n

  Ric::Color tex_dif;

  Ric::Color diffuse;

  //    qDebug() << "textre" << texture.isNull();

  //    const QImage *texture = (TextureContainer::instance()->get( QString::fromStdString(f->material().GetDifTexture())) );

  //    if(texture != NULL && f->material().has_texture() && !texture->isNull()){
  //      tex_dif = f->t_b(b_,texture);
  //    qDebug() << v_b << f->material().has_texture();
  diffuse =  f->t_b(b_);/*tex_dif;*/
  //      qDebug() << "has texture";
  //      diffuse = f->material().diffuse();
  //    }else{
  //      qDebug() << "just diffuse";
  //      diffuse = f->material().diffuse();
  //    }

  //  qDebug() << "hm";
  if(f->material().environment()){
    //    qDebug() << "ENVIRO";
    color_ = diffuse;
    return;
  }

  // For lighting calculations, do not use the actual face normal, but an interpolation of the vertex normals.

  foreach(SceneLight light, scene->transformed_light){
    l_ = (light.position-p_).Normalized();
    r_ = ((2*(l_*n_b)*n_b)-l_).Normalized();
    Ray shadow = Ray(p_,l_,(light.position-p_).Length(),near_length_,default_color_);
    bool shadow_hit = shadow.shadowCast(scene);
    //    qDebug() << "shadow cast";
    Ric::Color a,d,s,e;
    // Ambient Lighting for each light source.
    a = f->material().ambient() * light.material.ambient();
    double h = f->material().shininess();
    double f_att = (light.position-p_).Length();
    f_att = qMin(light.radius/(f_att*f_att),1.0);
    //if the point of the object can't see the light source, it will not consider the direct influence of it.
    if(!shadow_hit){

      d = f_att*( diffuse * light.material.diffuse() * (l()*n_b) );
      s = f_att*( (f->material().specular() * light.material.specular() * (r()*v())).Cap() );
    }else{
      //      qDebug() << "shadow hit";
      d = Ric::Color(0x00);
      s = Ric::Color(0x00);
    }
    AddColor( ((a + (d+(s^h)).Cap()).Cap()) );
  }
  if(f->material().environment_map()){
    Ric::Vector ref_dir = ((2*(v_*n_b)*n_b)-v_).Normalized();
    Ray env_recursive;
    env_recursive = Ray(p_,ref_dir,far_length_,near_length_,default_color_);
    env_recursive.calc(env_recursive.envCast(scene),scene,level-1,adv_light);
    color_ = env_recursive.color();
  }else if(level>0 && !f->material().environment()){
    Ray rf_recursive;
    Ray tr_recursive;

    qDebug() << f->material().reflection();
    if(f->material().reflection() > 0){
      Ric::Vector ref_dir = ((2*(v_*n_b)*n_b)-v_).Normalized();
      qDebug() << f->material().reflection();
      rf_recursive = Ray(p_,ref_dir,far_length_,near_length_,default_color_);
      rf_recursive.calc(rf_recursive.cast(scene),scene,level-1,adv_light);
    }
    qDebug() << f->material().transparency();
    if(f->material().transparency() > 0){
      double ref = 1.0/f->material().refraction();
      double cost1 = v_*n_b;
      double cost2 = sqrt(1-ref*ref*(1-cost1*cost1));
      Ric::Vector tr_dir = -ref*v_ + (ref*cost1-cost2)*n_b;
      tr_recursive = Ray(p_,tr_dir,far_length_,near_length_,default_color_);
      tr_recursive.calc(tr_recursive.cast(scene),scene,level-1,adv_light);
    }

    qDebug() << "Add Transparency";
    AddTransparencyAndReflection(f->material().transparency(),tr_recursive.color(),f->material().reflection(),rf_recursive.color());
  }else{

  }
}

bool Ray::hit() const
{
  return hit_;
}

double Ray::t() const
{
  return t_;
}

Ric::Vector Ray::o() const
{
  return o_;
}

Ric::Color Ray::color() const
{
  return color_;
}
Ric::Vector Ray::n() const
{
  return n_;
}

Ric::Vector Ray::l() const
{
  return l_;
}

Ric::Vector Ray::r() const
{
  return r_;
}

Ric::Vector Ray::v() const
{
  return v_;
}

Ric::Vector Ray::p() const
{
  return p_;
}

Ric::Vector Ray::b() const
{
  return b_;
}

void Ray::AddColor(const Ric::Color &color)
{
  color_ += color;
}

void Ray::AddTransparencyAndReflection(const float &tr, const Ric::Color &tr_color, const float &rf, const Ric::Color &rf_color)
{
  color_ = (tr*tr_color) + (rf*rf_color) + ((1-tr-rf)*color_);
  //  color_ = /*(tr*tr_color) + */(*rf_color) + ((0.0)*color_);
}

