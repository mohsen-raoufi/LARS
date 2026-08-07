QT += testlib core widgets
CONFIG += qt warn_on testcase
TEMPLATE = app
TARGET = tst_koc

INCLUDEPATH += ../../
INCLUDEPATH += /usr/local/include/opencv4

LIBS += -L/usr/local/lib -lopencv_core

SOURCES += tst_koc.cpp \
           ../../Kilobot/kilobotoverheadcontroller.cpp \
           ../../ohc/serialconn.cpp \
           ../../ohc/intelhex.cpp

HEADERS += ../../Kilobot/kilobotoverheadcontroller.h \
           ../../ohc/serialconn.h \
           ../../ohc/packet.h

include(../coverage.pri)
