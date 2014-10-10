#ifndef OPTIONS_H
#define OPTIONS_H

#include <QColor>
#include <QMap>
#include <QString>
class Options
{
public:
  static Options *instance();

  bool options_changed() const;
  void options_applied();

  float initial_zoom() const;
  float zoom_to_size() const;
  float max_zoom() const;
  float min_zoom() const;

  float initial_rot_x() const;
  float initial_rot_y() const;
  float initial_rot_z() const;

  float rot_to_angle() const;

  float normal_size() const;

  bool get_option(QString option);
  void set_option(QString option, bool v);

  void setVoxelScene(QString scene);
  QString getVoxelScene() const;

  QColor clear_color() const;
private :
  Options();

  static Options *instance_;

  bool options_changed_;

  // Scene Options
  const float initial_zoom_;
  const float max_zoom_;
  const float min_zoom_;
  const float zoom_to_size_;

  const float initial_rot_x_;
  const float initial_rot_y_;
  const float initial_rot_z_;
  const float rot_to_angle_;

  // Artifacts Options
  float normal_size_;

  QMap<QString,bool> check_options_;

  QString voxel_scene_;

  QColor clear_color_;
};

#endif // OPTIONS_H
