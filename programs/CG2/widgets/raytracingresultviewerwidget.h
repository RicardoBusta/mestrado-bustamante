#ifndef RAYTRACINGRESULTVIEWERWIDGET_H
#define RAYTRACINGRESULTVIEWERWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QTimer>

class Scene;
class RayTracingThread;

namespace Ui {
  class RayTracingResultViewerWidget;
}

class RayTracingResultViewerWidget : public QDialog
{
  Q_OBJECT
public:
  explicit RayTracingResultViewerWidget(const Scene *scene, const QSize &img_size, const int &level, QWidget *parent = 0);
  ~RayTracingResultViewerWidget();

private:
  Ui::RayTracingResultViewerWidget *ui;

  const Scene *scene_;

  QImage image_;

  QTimer auto_update_timer;

  int auto_update_steps;

  QVector<RayTracingThread*> rtt;
  QVector<QThread*> thread;

  int level_;
private slots:
//  void RayTracingStep();
  void UpdateImage();
  void CancelExecution();

signals:
  void StartWork();  
};

#endif // RAYTRACINGRESULTVIEWERWIDGET_H
