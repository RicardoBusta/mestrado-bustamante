#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QMap>
#include <QOpenGLShaderProgram>
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

private:
    ModelMap * models_;

    QPoint last_click_;
    QPoint delta_;
    QPoint auto_delta_;

    QOpenGLShaderProgram shader_program_;

    QTimer * timer_;

    float zoom_;
    float rotx_;
    float roty_;
private slots:
    void AutoRotate();
    void LoadTexture();
};

#endif // GLWIDGET_H
