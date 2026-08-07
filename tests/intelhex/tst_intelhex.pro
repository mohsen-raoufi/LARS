QT += testlib core
CONFIG += qt warn_on testcase
TEMPLATE = app
TARGET = tst_intelhex

INCLUDEPATH += ../../

SOURCES += tst_intelhex.cpp \
           ../../ohc/intelhex.cpp

HEADERS += ../../ohc/intelhex.h

include(../coverage.pri)
