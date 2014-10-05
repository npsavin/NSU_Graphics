#-------------------------------------------------
#
# Project created by QtCreator 2014-02-23T22:21:00
#
#-------------------------------------------------

QT       += core gui xml
CONFIG += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = circle
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    drawwidget.cpp \
    circle.cpp

HEADERS  += mainwindow.h \
    drawwidget.h \
    circle.h

FORMS    += mainwindow.ui
