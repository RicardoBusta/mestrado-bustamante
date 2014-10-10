#ifndef RAYTRACINGTHREAD_H
#define RAYTRACINGTHREAD_H

#include <QObject>
#include <QTimer>
#include <QRect>
#include <QImage>

class Scene;

class RayTracingThread : public QObject
{
  Q_OBJECT
public:
  explicit RayTracingThread(const QRect &rect, const int &id, const float &prop_x, const float &prop_y, const float &val_x, const float &val_y, const Scene *scene, QObject *parent=0);
  virtual ~RayTracingThread();

  const QRect rect;
  const float prop_x;
  const float prop_y;
  const float val_x;
  const float val_y;
  const int id;
  const Scene *scene_;

  bool aborted;

  QImage image_;

  int level_;

private:
  static int id_count;
signals:
  void Finished();
public slots:
  void Work();
};

#endif // RAYTRACINGTHREAD_H
