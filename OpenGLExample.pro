#-------------------------------------------------
#
# Project created by QtCreator 2016-10-03T15:08:37
#
#-------------------------------------------------

QT       +=  core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenGLExample
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
    meshfactory.cpp \
    OpenGLExample.cpp \
    shape.cpp \
    rectangle.cpp \
    triangle.cpp \
    ellipse.cpp \
    box.cpp \
    ellipsoid.cpp \
    cone.cpp


HEADERS  += mainwindow.h\
    meshfactory.h \
    OpenGLExample.h \
    shape.h \
    rectangle.h \
    triangle.h \
    ellipse.h \
    box.h \
    ellipsoid.h \
    cone.h

FORMS    += mainwindow.ui
RESOURCES += \
    GLShaders.qrc
