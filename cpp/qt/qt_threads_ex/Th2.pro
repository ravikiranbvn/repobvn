#-------------------------------------------------
#
# Project created by QtCreator 2017-01-15T16:30:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Th2
TEMPLATE = app

QT         += widgets
CONFIG     += qt


SOURCES += main.cpp\
        mainwindow.cpp \
    countworker.cpp \
    infinitecountworker.cpp \


HEADERS  += mainwindow.h \
    countworker.h \
    infinitecountworker.h \
    portablesleep.h

FORMS    += mainwindow.ui
MOC_DIR     = build
OBJECTS_DIR = build
DEST_DIR    = .
