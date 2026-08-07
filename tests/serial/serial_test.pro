QT += testlib core
CONFIG += qt warn_on testcase
TEMPLATE = app
TARGET = tst_serialconn

INCLUDEPATH += ../../

SOURCES += tst_serialconn.cpp \
           ../../ohc/serialconn.cpp \
           ../../ohc/intelhex.cpp

HEADERS += ../../ohc/serialconn.h \
           ../../ohc/intelhex.h \
           ../../ohc/packet.h

include(../coverage.pri)
