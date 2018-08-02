#-------------------------------------------------
#
# Project created by QtCreator 2016-12-26T22:43:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chatbox
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH +=/home/ravikiranbvn/HDE/x86_64.linux/include/dcps/C++/SACPP/
INCLUDEPATH +=/home/ravikiranbvn/HDE/x86_64.linux/include/dcps/C++/SACPP/mapping
INCLUDEPATH +=/home/ravikiranbvn/HDE/x86_64.linux/include
INCLUDEPATH +=/home/ravikiranbvn/HDE/x86_64.linux/include/sys
INCLUDEPATH +=/home/ravikiranbvn/HDE/x86_64.linux/include/include
INCLUDEPATH +=/home/ravikiranbvn/HDE/x86_64.linux/include/posix/include
INCLUDEPATH +=/home/ravikiranbvn/QT_E/DSS_project/DDS_Chatbox/IDL

SOURCES += main.cpp\
        mainwindow.cpp \
    ../IDL/chatboxSplDcps.cpp \
    ../IDL/chatboxDcps.cpp \
    ../IDL/chatboxDcps_impl.cpp \
    ../IDL/chatbox.cpp \
    publisher.cpp \
    subscriber.cpp \
    CheckStatus.cpp

HEADERS  += mainwindow.h \
    ../IDL/chatboxSplDcps.h \
    ../IDL/chatboxDcps.h \
    ../IDL/chatboxDcps_impl.h \
    ../IDL/chatbox.h \
    ../IDL/ccpp_chatbox.h \
    publisher.h \
    subscriber.h \
    CheckStatus.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../HDE/x86_64.linux/lib/release/ -lddsos
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../HDE/x86_64.linux/lib/debug/ -lddsos
else:unix: LIBS += -L$$PWD/../../../../HDE/x86_64.linux/lib/ -lddsos

INCLUDEPATH += $$PWD/../../../../HDE/x86_64.linux/include
DEPENDPATH += $$PWD/../../../../HDE/x86_64.linux/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../HDE/x86_64.linux/lib/release/ -lddsutil
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../HDE/x86_64.linux/lib/debug/ -lddsutil
else:unix: LIBS += -L$$PWD/../../../../HDE/x86_64.linux/lib/ -lddsutil

INCLUDEPATH += $$PWD/../../../../HDE/x86_64.linux/include
DEPENDPATH += $$PWD/../../../../HDE/x86_64.linux/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../HDE/x86_64.linux/lib/release/ -lddsdatabase
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../HDE/x86_64.linux/lib/debug/ -lddsdatabase
else:unix: LIBS += -L$$PWD/../../../../HDE/x86_64.linux/lib/ -lddsdatabase

INCLUDEPATH += $$PWD/../../../../HDE/x86_64.linux/include
DEPENDPATH += $$PWD/../../../../HDE/x86_64.linux/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../HDE/x86_64.linux/lib/release/ -lddsconf
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../HDE/x86_64.linux/lib/debug/ -lddsconf
else:unix: LIBS += -L$$PWD/../../../../HDE/x86_64.linux/lib/ -lddsconf

INCLUDEPATH += $$PWD/../../../../HDE/x86_64.linux/include
DEPENDPATH += $$PWD/../../../../HDE/x86_64.linux/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../HDE/x86_64.linux/lib/release/ -lddsconfparser
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../HDE/x86_64.linux/lib/debug/ -lddsconfparser
else:unix: LIBS += -L$$PWD/../../../../HDE/x86_64.linux/lib/ -lddsconfparser

INCLUDEPATH += $$PWD/../../../../HDE/x86_64.linux/include
DEPENDPATH += $$PWD/../../../../HDE/x86_64.linux/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../HDE/x86_64.linux/lib/release/ -lddsserialization
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../HDE/x86_64.linux/lib/debug/ -lddsserialization
else:unix: LIBS += -L$$PWD/../../../../HDE/x86_64.linux/lib/ -lddsserialization

INCLUDEPATH += $$PWD/../../../../HDE/x86_64.linux/include
DEPENDPATH += $$PWD/../../../../HDE/x86_64.linux/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../HDE/x86_64.linux/lib/release/ -lddskernel
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../HDE/x86_64.linux/lib/debug/ -lddskernel
else:unix: LIBS += -L$$PWD/../../../../HDE/x86_64.linux/lib/ -lddskernel

INCLUDEPATH += $$PWD/../../../../HDE/x86_64.linux/include
DEPENDPATH += $$PWD/../../../../HDE/x86_64.linux/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../HDE/x86_64.linux/lib/release/ -lddsuser
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../HDE/x86_64.linux/lib/debug/ -lddsuser
else:unix: LIBS += -L$$PWD/../../../../HDE/x86_64.linux/lib/ -lddsuser

INCLUDEPATH += $$PWD/../../../../HDE/x86_64.linux/include
DEPENDPATH += $$PWD/../../../../HDE/x86_64.linux/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../HDE/x86_64.linux/lib/release/ -ldcpsgapi
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../HDE/x86_64.linux/lib/debug/ -ldcpsgapi
else:unix: LIBS += -L$$PWD/../../../../HDE/x86.linux/lib/ -ldcpsgapi

INCLUDEPATH += $$PWD/../../../../HDE/x86_64.linux/include
DEPENDPATH += $$PWD/../../../../HDE/x86_64.linux/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../HDE/x86_64.linux/lib/release/ -ldcpssacpp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../HDE/x86_64.linux/lib/debug/ -ldcpssacpp
else:unix: LIBS += -L$$PWD/../../../../HDE/x86_64.linux/lib/ -ldcpssacpp

INCLUDEPATH += $$PWD/../../../../HDE/x86_64.linux/include
DEPENDPATH += $$PWD/../../../../HDE/x86_64.linux/include

DISTFILES += \
    ../IDL/chatbox.idl
