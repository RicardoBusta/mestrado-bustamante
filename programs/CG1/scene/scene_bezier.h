#ifndef SCENE_BEZIER_H
#define SCENE_BEZIER_H

#include "programs/CG1/opengl/scene.h"

#include <QVector3D>

namespace Ui{
  class BezierWidget;
}

class SceneBezier : public Scene
{
  Q_OBJECT
public:
  explicit SceneBezier(QObject *parent = 0);

private:
    virtual void buildControlWidget();
    void setup_spec();
    void drawObjects() const;

    void recalculateControlPoints();
    void recalculateSurface();

    QVector< QVector<QVector3D> > control_points_;
    QVector< QVector<QVector3D> > surface_points_;
    QVector< QVector<QColor> >    surface_colors_;

    QVector3D surfacePoint(float u, float v) const;

    int control_size_;
    float control_size_f_;
    int surface_size_;
    float surface_size_f_;

    QPoint current_control_point_;

    Ui::BezierWidget *ui;

    QVector3D calculateNormal(const QVector3D &v1, const QVector3D &v2, const QVector3D &v3) const;

private slots:
    void currentControlPointChanged();
    void controlPointValueXChanged();
    void controlPointValueYChanged();
    void controlPointValueZChanged();

    void controlSizeChanged();
};

#endif // SCENE_BEZIER_H
