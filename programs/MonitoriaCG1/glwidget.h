#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QMap>
#include <QGLShaderProgram>
#include <QOpenGLTexture>

#include "model.h"

class GLWidget : public QGLWidget {
    Q_OBJECT
public:
    GLWidget(QWidget * parent = 0);
    ~GLWidget();

    void SetModelRef(ModelMap * models);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void SetShaders(const QString &v_shader, const QString &f_shader);

private:
    ModelMap * models_;

    QPoint last_click_;
    QPoint delta_;
    QPoint auto_delta_;

    QGLShaderProgram shader_program_;

    QTimer * timer_;

    float zoom_;
    float rotx_;
    float roty_;

    bool perspective_;

    bool initialized_;

    void SetProjection(int w, int h);
private slots:
    void AutoRotate();
    void LoadTexture();
    void TogglePerspective();
};

#endif // GLWIDGET_H
