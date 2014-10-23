#include "options.h"

#include <QDebug>

Options *Options::instance_ = NULL;

Options::Options():
  options_changed_(true),
  // Scene
  initial_zoom_(0.2f),
  zoom_to_size_(1000.f),
  max_zoom_(10.0f),
  min_zoom_(0.01f),
  initial_rot_x_(45.f),
  initial_rot_y_(0.f),
  initial_rot_z_(0.f),
  rot_to_angle_(0.2f),
  // Artifacts
  normal_size_(0.2f),
  clear_color_(QColor(Qt::black))
{
}

Options *Options::instance()
{
  if(NULL == instance_)
    instance_ = new Options;

  return instance_;
}

bool Options::options_changed() const
{
  return options_changed_;
}

void Options::options_applied()
{
  options_changed_ = false;
}

float Options::initial_zoom() const
{
  return initial_zoom_;
}

float Options::initial_rot_x() const
{
  return initial_rot_x_;
}

float Options::initial_rot_y() const
{
  return initial_rot_y_;
}

float Options::initial_rot_z() const
{
  return initial_rot_z_;
}

float Options::rot_to_angle() const
{
  return rot_to_angle_;
}

float Options::zoom_to_size() const
{
  return zoom_to_size_;
}

float Options::max_zoom() const
{
  return max_zoom_;
}

float Options::min_zoom() const
{
  return min_zoom_;
}

float Options::normal_size() const
{
  return normal_size_;
}

bool Options::get_option(QString option)
{
  if(check_options_.contains(option)){
  return check_options_[option];
  }else{
    qWarning() << "Invalid Option:" << option;
    return false;
  }
}

void Options::set_option(QString option, bool v)
{
  options_changed_ = true;
  if(check_options_.contains(option)){
    check_options_[option] = v;
  }else{
    check_options_.insert(option,v);
  }
}

void Options::setVoxelScene(QString scene)
{
  voxel_scene_ = scene;
}

QString Options::getVoxelScene() const
{
  return voxel_scene_;
}

QColor Options::clear_color() const
{
  return clear_color_;
}
