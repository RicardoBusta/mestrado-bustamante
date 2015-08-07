#-------------------------------------------------
#
# Project created by QtCreator 2015-08-06T09:49:38
#
#-------------------------------------------------

lessThan(QT_MAJOR_VERSION, 5){
  message(Your qt version must be 5.0 or higher.)
} else {
  QT += core gui widgets opengl

  TARGET = MonitoriaCG1
  TEMPLATE = app

  SOURCES += \
      main.cpp\
      mainwindow.cpp \
      model.cpp \
      glwidget.cpp

  HEADERS  += \
      mainwindow.h \
      model.h \
      glwidget.h

  FORMS    += \
      mainwindow.ui
}
