#include "scene_bezier.h"

#include <QtOpenGL>
#include <QDebug>

#include "programs/CG1/utils/common.h"
#include "ui_bezier_widget.h"
#include "programs/CG1/utils/options.h"

SceneBezier::SceneBezier(QObject *parent) :
  Scene(parent)
{
  control_size_ = 4;
  control_size_f_ = float(control_size_);
  surface_size_ = 20;
  surface_size_f_ = float(surface_size_);
  current_control_point_ = QPoint(0,0);

}

void SceneBezier::buildControlWidget()
{
  ui = new Ui::BezierWidget;
  ui->setupUi(control_widget_);

  ui->spin_p_i->setMinimum(0);
  ui->spin_p_i->setMaximum(control_size_-1);
  ui->spin_p_j->setMinimum(0);
  ui->spin_p_j->setMaximum(control_size_-1);

  ui->spin_c_s->setValue(control_size_);

  connect(ui->spin_p_i,SIGNAL(valueChanged(int)),this,SLOT(currentControlPointChanged()));
  connect(ui->spin_p_j,SIGNAL(valueChanged(int)),this,SLOT(currentControlPointChanged()));

  connect(ui->spin_v_x,SIGNAL(valueChanged(double)),this,SLOT(controlPointValueXChanged()));
  connect(ui->spin_v_y,SIGNAL(valueChanged(double)),this,SLOT(controlPointValueYChanged()));
  connect(ui->spin_v_z,SIGNAL(valueChanged(double)),this,SLOT(controlPointValueZChanged()));

  connect(ui->spin_c_s,SIGNAL(valueChanged(int)),this,SLOT(controlSizeChanged()));

  currentControlPointChanged();
}

void SceneBezier::setup_spec()
{
  recalculateControlPoints();
  recalculateSurface();
}

void SceneBezier::drawObjects() const
{
  glPushMatrix();
  glPushAttrib(GL_ALL_ATTRIB_BITS);

  glScalef(zoom(),zoom(),zoom());
  glRotatef(rot_x(),1,0,0);
  glRotatef(rot_y(),0,1,0);
  glRotatef(rot_z(),0,0,1);

  glRotatef(180,0,1,0);
  glRotatef(90,1,0,0);

  // Draw Control Points
  glDisable(GL_LIGHTING);
  glDisable(GL_TEXTURE_2D);
  glPointSize(10);
  glBegin(GL_POINTS);
  for(int i=0;i<control_size_;i++){
    for(int j=0;j<control_size_;j++){
      if(i == current_control_point_.x() && j == current_control_point_.y()){
        glColor3f(1,0,0);
      }else{
        glColor3f(1,1,1);
      }
      GlVertex(control_points_[i][j]);
    }
  }
  glEnd();

  // Draw Control Lines
  glDisable(GL_CULL_FACE);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glBegin(GL_QUADS);
  glColor3f(1,1,0);
  for(int i=0;i<control_size_-1;i++){
    for(int j=0;j<control_size_-1;j++){
      GlVertex(control_points_[i][j]);
      GlVertex(control_points_[i+1][j]);
      GlVertex(control_points_[i+1][j+1]);
      GlVertex(control_points_[i][j+1]);
    }
  }
  glEnd();

  // Draw Surface
  if(Options::instance()->get_option("check_wireframe")){
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
  }else{
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
  }
  glBegin(GL_QUADS);
  for(int i=0;i<surface_size_-1;i++){
    for(int j=0;j<surface_size_-1;j++){
      GlColor(surface_colors_[i][j]);
      GlVertex(surface_points_[i][j]);
      GlColor(surface_colors_[i+1][j]);
      GlVertex(surface_points_[i+1][j]);
      GlColor(surface_colors_[i+1][j+1]);
      GlVertex(surface_points_[i+1][j+1]);
      GlColor(surface_colors_[i][j+1]);
      GlVertex(surface_points_[i][j+1]);
    }
  }
  glEnd();

  glPopAttrib();
  glPopMatrix();
}

void SceneBezier::recalculateControlPoints()
{
  // Build Control Points
  control_points_.resize(control_size_);
  for(int i=0;i<control_size_;i++){
    float u = (2.0f*float(i)/(control_size_f_-1.0f))-1.0f;
    control_points_[i].resize(control_size_);
    for(int j=0;j<control_size_;j++){
      float v = (2.0f*float(j)/(control_size_f_-1.0f))-1.0f;
      //      control_points_[i][j] = QVector3D(u,v,0);
      control_points_[i][j].setX(u);
      control_points_[i][j].setY(v);
    }
  }
}

void SceneBezier::recalculateSurface()
{
  // Build Surface Points
  surface_points_.resize(surface_size_);
  surface_colors_.resize(surface_size_);
  for(int i=0;i<surface_size_;i++){
    float x = float(i)/(surface_size_f_-1.f);
    surface_points_[i].resize(surface_size_);
    surface_colors_[i].resize(surface_size_);
    for(int j=0;j<surface_size_;j++){
      float y = float(j)/(surface_size_f_-1.f);
      surface_points_[i][j] = surfacePoint(x,y);
      surface_colors_[i][j] = QColor(255*x,255*y,255*(1.0f-(x*y)));
    }
  }
}

QVector3D SceneBezier::surfacePoint(float u, float v) const
{
  int m=control_size_-1;
  int n=control_size_-1;
  QVector3D sum;
  for(int i=0;i<=n;i++){
    float bu = bernstein(u,n,i);
    for(int j=0;j<=m;j++){
      float bj = bernstein(v,m,j);
      sum = (bu * bj * control_points_[i][j]) + sum;
    }
  }
  return sum;
}

void SceneBezier::currentControlPointChanged()
{
  current_control_point_ = QPoint(ui->spin_p_i->value(),ui->spin_p_j->value());

  QVector3D p = control_points_[current_control_point_.x()][current_control_point_.y()];

  disconnect(ui->spin_v_x,SIGNAL(valueChanged(double)),this,SLOT(controlPointValueXChanged()));
  disconnect(ui->spin_v_y,SIGNAL(valueChanged(double)),this,SLOT(controlPointValueYChanged()));
  disconnect(ui->spin_v_z,SIGNAL(valueChanged(double)),this,SLOT(controlPointValueZChanged()));

  ui->spin_v_x->setValue( p.x() );
  ui->spin_v_y->setValue( p.y() );
  ui->spin_v_z->setValue( p.z() );

  connect(ui->spin_v_x,SIGNAL(valueChanged(double)),this,SLOT(controlPointValueXChanged()));
  connect(ui->spin_v_y,SIGNAL(valueChanged(double)),this,SLOT(controlPointValueYChanged()));
  connect(ui->spin_v_z,SIGNAL(valueChanged(double)),this,SLOT(controlPointValueZChanged()));
}

void SceneBezier::controlPointValueXChanged()
{
  control_points_[current_control_point_.x()][current_control_point_.y()].setX( ui->spin_v_x->value() );

  recalculateSurface();
}

void SceneBezier::controlPointValueYChanged()
{
  control_points_[current_control_point_.x()][current_control_point_.y()].setY( ui->spin_v_y->value() );

  recalculateSurface();
}

void SceneBezier::controlPointValueZChanged()
{
  control_points_[current_control_point_.x()][current_control_point_.y()].setZ( ui->spin_v_z->value() );

  recalculateSurface();
}

void SceneBezier::controlSizeChanged()
{
  control_size_ = ui->spin_c_s->value();
  control_size_f_ = float(control_size_);

  ui->spin_p_i->setMinimum(0);
  ui->spin_p_i->setMaximum(control_size_-1);
  ui->spin_p_j->setMinimum(0);
  ui->spin_p_j->setMaximum(control_size_-1);

  recalculateControlPoints();
  recalculateSurface();
}
