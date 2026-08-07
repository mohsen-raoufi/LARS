QT += testlib core gui
CONFIG += qt warn_on testcase
TEMPLATE = app
TARGET = tst_worldmodel

DEFINES += FOR_KILOBOT

INCLUDEPATH += ../../

# Resolved via pkg-config instead of hardcoded paths, which don't agree
# across apt/Homebrew/source-built installs.
CONFIG += link_pkgconfig
PKGCONFIG += opencv4 igraph

SOURCES += tst_worldmodel.cpp \
           ../../ui/worldmodel.cpp

HEADERS += ../../ui/worldmodel.h

include(../coverage.pri)
