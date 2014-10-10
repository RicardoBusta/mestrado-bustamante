#-------------------------------------------------
#
# Project created by QtCreator 2014-02-13T06:44:26
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CG2
TEMPLATE = app


SOURCES += \
    main.cpp\
    widgets/mainwindow.cpp \
    application.cpp \
    ray.cpp \
    scene/sceneobject.cpp \
    scene/scene.cpp \
    widgets/glwidget.cpp \
    widgets/raytracingwidget.cpp \
    structures.cpp \
    structures/matrix4x4.cpp \
    structures/vector.cpp \
    structures/color.cpp \
    widgets/outerviewwidget.cpp \
    structures/material.cpp \
    scene/scenelight.cpp \
    scene/triangleface.cpp \
    openclloader.cpp \
    openclraytracing.cpp \
    scene/objloader.cpp \
    scene/openglauxfunctions.cpp \
    widgets/raytracingresultviewerwidget.cpp \
    widgets/raytracingthread.cpp \
    structures/texturecontainer.cpp

HEADERS  += \
    widgets/mainwindow.h \
    application.h \
    ray.h \
    scene/sceneobject.h \
    scene/scene.h \
    widgets/glwidget.h \
    widgets/raytracingwidget.h \
    structures.h \
    structures/matrix4x4.h \
    structures/vector.h \
    structures/color.h \
    widgets/outerviewwidget.h \
    constants.h \
    structures/material.h \
    scene/scenelight.h \
    scene/triangleface.h \
    openclloader.h \
    openclloaderdefines.h \
    openclraytracing.h \
    scene/objloader.h \
    scene/openglauxfunctions.h \
    widgets/raytracingresultviewerwidget.h \
    widgets/raytracingthread.h \
    structures/texturecontainer.h

FORMS    += \
    widgets/mainwindow.ui \
    widgets/raytracingresultviewerwidget.ui

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    models/crystal_formations.mtl \
    models/crystal_formations.obj \
    models/cube.mtl \
    models/cube.obj \
    models/one_crystal.mtl \
    models/one_crystal.obj \
    models/car.mtl \
    models/car.obj \
    models/cubes.mtl \
    models/cubes.obj \
    models/cubes.png \
    models/spheres.obj \
    models/spheres.mtl \
    models/pyramid.obj \
    models/pyramid.mtl \
    models/environment.obj \
    models/environment.mtl \
    models/enviro_monkey.obj \
    models/enviro_monkey.mtl \
    models/enviro_ball.obj \
    models/enviro_ball.mtl \
    models/textured.obj \
    models/textured.mtl

unix:!macx:LIBS+= -ldl

INCLUDEPATH += $$PWD/includes/NVIDIA_SDK/OpenCL/common/inc
DEPENDPATH += $$PWD/includes/NVIDIA_SDK/OpenCL/common/inc
