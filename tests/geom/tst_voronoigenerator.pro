QT += testlib core
CONFIG += qt warn_on testcase
TEMPLATE = app
TARGET = tst_voronoigenerator

INCLUDEPATH += ../../
INCLUDEPATH += /usr/include/boost

SOURCES += tst_voronoigenerator.cpp \
           ../../ui/geom/voronoiGenerator.cpp

HEADERS += ../../ui/geom/voronoiGenerator.h

include(../coverage.pri)
