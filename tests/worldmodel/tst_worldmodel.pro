QT += testlib core gui
CONFIG += qt warn_on testcase
TEMPLATE = app
TARGET = tst_worldmodel

DEFINES += FOR_KILOBOT

INCLUDEPATH += ../../
INCLUDEPATH += /usr/local/include/opencv4
INCLUDEPATH += /usr/include/boost

LIBS += -L/usr/local/lib -lopencv_core -ligraph

SOURCES += tst_worldmodel.cpp \
           ../../ui/worldmodel.cpp

HEADERS += ../../ui/worldmodel.h

include(../coverage.pri)
