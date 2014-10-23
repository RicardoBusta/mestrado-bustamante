#include "scene_voxel.h"

#include <QtOpenGL>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>

#include "programs/CG1/opengl/textures.h"
#include "programs/CG1/utils/options.h"
#include "programs/CG1/opengl/opengl_typedef.h"

#include "ui_voxel_widget.h"

SceneVoxel::SceneVoxel(QObject *parent):
  Scene(parent)
{

}

SceneVoxel::~SceneVoxel()
{
}

void SceneVoxel::drawObjects() const
{
  glPushMatrix();
  glPushAttrib(GL_ALL_ATTRIB_BITS);

  glColor3f(1,1,1);

  if(Options::instance()->get_option("check_textures")){
    //    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_3D);
  }else{
    //    glDisable(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_3D);
  }

  //  glDisable(GL_DEPTH_TEST);
  glEnable ( GL_ALPHA_TEST ) ;
  glAlphaFunc ( GL_GREATER, 0.1f ) ;

  //  glDisable(GL_CULL_FACE);

  //  glMatrixMode(GL_TEXTURE);

  glScalef(zoom(),zoom(),zoom());
  glRotatef(rot_x(),1,0,0);
  glRotatef(rot_y(),0,1,0);
  glRotatef(rot_z(),0,0,1);

  glRotatef(180,0,1,0);
  glRotatef(90,1,0,0);


  //  glMatrixMode(GL_MODELVIEW);

  Textures::instance()->set3DTexture(Options::instance()->getVoxelScene());

  glBegin(GL_QUADS);

  int voxel_cube_dimension = Textures::instance()->getTextureSize(Options::instance()->getVoxelScene());
  float texel_size = 1.0f / float(voxel_cube_dimension-1);
  float voxel_size = 1.0f / float(voxel_cube_dimension);

  for(int i=0; i<voxel_cube_dimension; i++){
    float tex_layer = texel_size * i;
    float layer = 1.0 - (2.0*voxel_size*i) - 2*voxel_size;

    // Front
    glNormal3f(0,0,1);
    glTexCoord3f(0,0,tex_layer);
    glVertex3f(-1,-1,-layer);
    glTexCoord3f(1,0,tex_layer);
    glVertex3f(+1,-1,-layer);
    glTexCoord3f(1,1,tex_layer);
    glVertex3f(+1,+1,-layer);
    glTexCoord3f(0,1,tex_layer);
    glVertex3f(-1,+1,-layer);

    //Back
    glNormal3f(0,0,-1);
    glTexCoord3f(0,0,1.0-tex_layer);
    glVertex3f(-1,-1,layer);
    glTexCoord3f(0,1,1.0-tex_layer);
    glVertex3f(-1,+1,layer);
    glTexCoord3f(1,1,1.0-tex_layer);
    glVertex3f(+1,+1,layer);
    glTexCoord3f(1,0,1.0-tex_layer);
    glVertex3f(+1,-1,layer);

    // Top
    glNormal3f(0,1,0);
    glTexCoord3f(0,1-tex_layer,0);
    glVertex3f(-1,-layer,-1);
    glTexCoord3f(0,1-tex_layer,1);
    glVertex3f(-1,-layer,+1);
    glTexCoord3f(1,1-tex_layer,1);
    glVertex3f(+1,-layer,+1);
    glTexCoord3f(1,1-tex_layer,0);
    glVertex3f(+1,-layer,-1);

    // Bottom
    glNormal3f(0,-1,0);
    glTexCoord3f(0,tex_layer,0);
    glVertex3f(-1,layer,-1);
    glTexCoord3f(1,tex_layer,0);
    glVertex3f(+1,layer,-1);
    glTexCoord3f(1,tex_layer,1);
    glVertex3f(+1,layer,+1);
    glTexCoord3f(0,tex_layer,1);
    glVertex3f(-1,layer,+1);

    // Left
    glNormal3f(1,0,0);
    glTexCoord3f(tex_layer,1,0);
    glVertex3f(-layer,-1,-1);
    glTexCoord3f(tex_layer,0,0);
    glVertex3f(-layer,+1,-1);
    glTexCoord3f(tex_layer,0,1);
    glVertex3f(-layer,+1,+1);
    glTexCoord3f(tex_layer,1,1);
    glVertex3f(-layer,-1,+1);

    // Right
    glNormal3f(-1,0,0);
    glTexCoord3f(1.0-tex_layer,1,0);
    glVertex3f(layer,-1,-1);
    glTexCoord3f(1.0-tex_layer,1,1);
    glVertex3f(layer,-1,+1);
    glTexCoord3f(1.0-tex_layer,0,1);
    glVertex3f(layer,+1,+1);
    glTexCoord3f(1.0-tex_layer,0,0);
    glVertex3f(layer,+1,-1);
  }

  glEnd();

  glPopAttrib();
  glPopMatrix();
}

void SceneVoxel::setup_spec()
{
  Model::load(":/model/skydome.obj");

  skybox_ = Object::create("Skydome","skydome");
}

void SceneVoxel::buildControlWidget()
{
  Ui::VoxelWidget *ui = new Ui::VoxelWidget;
  ui->setupUi(control_widget_);

  ui->comboBox->addItem("voxel_scene.png");
  ui->comboBox->addItem("voxatron.png");
  ui->comboBox->addItem("ball.png");
  Options::instance()->setVoxelScene(ui->comboBox->currentText());
  connect(ui->comboBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(setVoxelScene(QString)));
}

void SceneVoxel::setVoxelScene(QString scene)
{
  Options::instance()->setVoxelScene(scene);
}
