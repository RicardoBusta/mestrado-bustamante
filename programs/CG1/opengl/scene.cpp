#include "scene.h"

#include <QtOpenGL>

#include "programs/CG1/utils/options.h"
#include "programs/CG1/opengl/textures.h"
#include "programs/CG1/opengl/shaders.h"
#include "programs/CG1/opengl/opengl.h"
#include "programs/CG1/cgapplication.h"
#include "programs/CG1/widgets/mainwindow.h"

Scene *Scene::instance_ = NULL;
QMap<QString,Scene*> Scene::scene_;
QString Scene::current_scene_ = "none";

Scene::Scene(QObject *parent):
  QObject(parent),
  skybox_(NULL),
  initialized_(false),
  zoom_(Options::instance()->initial_zoom()),
  rot_x_(Options::instance()->initial_rot_x()),
  rot_y_(Options::instance()->initial_rot_y()),
  rot_z_(Options::instance()->initial_rot_z()),
  control_widget_(NULL)
{
}

Scene::~Scene()
{
  for(QVector<Object*>::iterator it = objects_.begin(); it!= objects_.end(); it++){
    if((*it)!=NULL){
      delete (*it);
    }
  }
  if(skybox_!=NULL){
    delete skybox_;
  }
}

void Scene::setZoom(float zoom)
{
  float max_zoom = Options::instance()->max_zoom();
  float min_zoom = Options::instance()->min_zoom();

  if(zoom < min_zoom){
    zoom_ = min_zoom;
  }else if(zoom > max_zoom){
    zoom_ = max_zoom;
  }else{
    zoom_ = zoom;
  }
}

void Scene::applyCameraConstraint()
{
}

void Scene::setGuiMatrix(const Busta::Matrix4x4 &modelview, const Busta::Matrix4x4 &projection)
{
  qDebug() << "gui setting matrix";
  gui_modelview_ = modelview;
  gui_projection_ = projection;
}

void Scene::GlVertex(const QVector3D &v) const
{
  glVertex3f(v.x(),v.y(),v.z());
}

void Scene::GlColor(const QColor &c) const
{
  glColor3f(c.redF(),c.greenF(),c.blueF());
}

void Scene::GlNormal(const QVector3D &v) const
{
  glNormal3f(v.x(),v.y(),v.z());
}

void Scene::addZoom(int zoom)
{
  setZoom( zoom_ + zoom_*float(zoom)/Options::instance()->zoom_to_size() );
}

void Scene::rotate(int rot_x, int rot_y, int rot_z)
{
  float rot_to_angle = Options::instance()->rot_to_angle();
  rot_x_ += rot_x*rot_to_angle;
  rot_y_ += rot_y*rot_to_angle;
  rot_z_ += rot_z*rot_to_angle;
}

void Scene::initialize()
{
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);

  glShadeModel(GL_SMOOTH);
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

void Scene::setup()
{
  if(initialized_) return;

  glLoadIdentity();
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);

  glShadeModel(GL_SMOOTH);
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable( GL_BLEND );


  setup_spec();
  initialized_ = true;
}

void Scene::resize(int w, int h)
{
  int size = qMax(w,h);
  glViewport((w-size)/2.0,(h-size)/2.0,size,size);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //  glOrtho(-1,1,-1,1,-50,50);
  glFrustum(-.1,.1,-.1,.1,0.1,1000);
  glTranslatef(0,0,-1);

  glMatrixMode(GL_MODELVIEW);
}

void Scene::setOptions()
{
  if(Options::instance()->options_changed()){
    const QColor &cc = Options::instance()->clear_color();
    glClearColor(cc.redF(),cc.greenF(),cc.blueF(),1.0f);

    if(Options::instance()->get_option("check_textures")){
      glEnable(GL_TEXTURE_2D);
      //glEnable(GL_TEXTURE_3D);
    }else{
      glDisable(GL_TEXTURE_2D);
      //glDisable(GL_TEXTURE_3D);
    }

    glMatrixMode(GL_PROJECTION);

    if(!gui_projection_.isIdentity()){
      glLoadMatrixf(gui_projection_.data());
    }else{
      glLoadIdentity();
      if(Options::instance()->get_option("check_perspective")){
        glFrustum(-.1,.1,-.1,.1,0.1,1000);
        glTranslatef(0,0,-1);
      }else{
        glOrtho(-1,1,-1,1,-50,50);
      }
    }

    glMatrixMode(GL_MODELVIEW);

    Options::instance()->options_applied();
  }
}

void Scene::clear() const
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glLoadIdentity();

  if(Options::instance()->get_option("check_wireframe")){
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
  }else{
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
  }
}

void Scene::pre_draw() const
{
  preDraw();
  drawSkybox();
}

void Scene::preDraw() const
{

}

void Scene::draw() const
{
  drawObjects();
}

void Scene::post_draw() const
{
  postDraw();
}

void Scene::drawArtifacts() const
{
  glPushMatrix();

  glPushAttrib(GL_ALL_ATTRIB_BITS);
  glDisable(GL_LIGHTING);

  glRotatef(rot_x_,1,0,0);
  glRotatef(rot_y_,0,1,0);
  glRotatef(rot_z_,0,0,1);

  glScalef(zoom_,zoom_,zoom_);

  for(int i=0;i<objects_.size(); i++){
    if(objects_[i]!=NULL){
      objects_[i]->drawArtifacts();
    }
  }

  if(Options::instance()->get_option("check_axis")){
    glDisable(GL_TEXTURE_2D);
    glBegin(GL_LINES);
    // Axis
    glColor3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(1,0,0);

    glColor3f(0,1,0);
    glVertex3f(0,0,0);
    glVertex3f(0,1,0);

    glColor3f(0,0,1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,1);
    glEnd();
  }

  glPopAttrib();
  glPopMatrix();
}

void Scene::postDraw() const
{
}

void Scene::drawSkybox() const
{
  glPushAttrib(GL_ALL_ATTRIB_BITS);

  if(Options::instance()->get_option("check_textures")){
    glEnable(GL_TEXTURE_2D);
  }else{
    glDisable(GL_TEXTURE_2D);
  }

  // Draw Skybox
  if(Options::instance()->get_option("check_skydome")){
    glPushMatrix();
    glLoadIdentity();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_LIGHTING);

    glRotatef(rot_x_,1,0,0);
    glRotatef(rot_y_,0,1,0);
    glRotatef(rot_z_,0,0,1);

    if(skybox_!=NULL){
      skybox_->draw();
    }

    glPopAttrib();

    glPopMatrix();
  }
  glPopAttrib();
}

void Scene::drawObjects() const
{
  // Draw Objects
  glPushMatrix();
  glScalef(zoom_,zoom_,zoom_);
  glRotatef(rot_x_,1,0,0);
  glRotatef(rot_y_,0,1,0);
  glRotatef(rot_z_,0,0,1);

  glMultMatrixf(gui_modelview_.data());

//  glMatrixMode(GL_PROJECTION);
//  glMultMatrixf(gui_projection_.data());
//  glMatrixMode(GL_MODELVIEW);

  //glRotatef(90,1,0,0);
  //  glFrustum(-.1,.1,-.1,.1,1,10);

  for(int i=0;i<objects_.size(); i++){
    if(objects_[i]!=NULL){
      objects_[i]->preDraw();
      objects_[i]->draw();
    }
  }
  glPopMatrix();
}

float Scene::zoom() const
{
  return zoom_;
}

float Scene::rot_x() const
{
  return rot_x_;
}

float Scene::rot_y() const
{
  return rot_y_;
}

float Scene::rot_z() const
{
  return rot_z_;
}

QWidget *Scene::controlWidget()
{
  if(control_widget_==NULL){
    control_widget_ = new QWidget();
    ((CGApplication*)(qApp))->getMainWindow()->addSceneControlWidget(control_widget_);
    buildControlWidget();
  }

  return control_widget_;
}

void Scene::buildControlWidget()
{

}

void Scene::step()
{
  if(Options::instance()->get_option("check_animation")){
    for(int i=0;i<objects_.size(); i++){
      if(objects_[i]!=NULL){
        objects_[i]->step();
      }
    }
  }
}

void Scene::addScene(QString scene_name, Scene *scene)
{
  qDebug() << "Adding Scene" << scene_name;
  if(scene_.contains(scene_name)){
    qWarning () << "scene with repeated name.";
    return;
  }

  scene_.insert(scene_name,scene);
}

bool Scene::valid()
{
  if(scene_.contains(current_scene_) && scene_[current_scene_]!=NULL){
    return true;
  }
  return false;
}

Scene *Scene::current()
{
  if(valid()){
    return scene_[current_scene_];
  }else{
    return NULL;
  }
}

QString Scene::current_name()
{
  return current_scene_;
}

void Scene::setCurrent(QString scene_name)
{
  if(scene_.contains(scene_name)){
    current_scene_ = scene_name;
    scene_[current_scene_]->setup();
  }else{
    qWarning () << "Scene do not exist.";
  }
}

QStringList Scene::scene_list()
{
  QStringList out;
  for(QMap<QString,Scene*>::iterator it = scene_.begin(); it!= scene_.end(); it++){
    out.push_back(it.key());
  }
  out.sort();
  return out;
}

QStringList Scene::getObjectList() const
{
  QStringList list;

  for(QVector<Object*>::const_iterator it = objects_.begin(); it!= objects_.end(); it++){
    list.push_back((*it)->name());
  }

  list.sort();

  return list;
}

void Scene::setup_spec()
{
}
