#-------------------------------------------------
#
# Project created by QtCreator 2014-03-27T01:34:45
#
#-------------------------------------------------

QT       += core gui xml
CONFIG   += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = polygon
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    polygon.cpp \
    drawwidget.cpp

HEADERS  += mainwindow.h \
    polygon.h \
    drawwidget.h

FORMS    += mainwindow.ui
