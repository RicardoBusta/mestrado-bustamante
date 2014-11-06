#-------------------------------------------------
#
# Project created by QtCreator 2014-09-04T22:23:33
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ExampleCG1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    matrix4x4.cpp \
    vector4.cpp \
    glvertex.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    matrix4x4.h \
    vector4.h \
    glvertex.h

FORMS    += mainwindow.ui
