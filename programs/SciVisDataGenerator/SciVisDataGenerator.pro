TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

SOURCES += main.cpp

include(deployment.pri)
qtcAddDeployment()

