QT += testlib core widgets
CONFIG += qt warn_on testcase
TEMPLATE = app
TARGET = tst_koc

INCLUDEPATH += ../../

# Resolved via pkg-config instead of a hardcoded path (see tests/kilobot/kilobot_test.pro).
CONFIG += link_pkgconfig
PKGCONFIG += opencv4

SOURCES += tst_koc.cpp \
           ../../Kilobot/kilobotoverheadcontroller.cpp \
           ../../ohc/serialconn.cpp \
           ../../ohc/intelhex.cpp

HEADERS += ../../Kilobot/kilobotoverheadcontroller.h \
           ../../ohc/serialconn.h \
           ../../ohc/packet.h

include(../coverage.pri)
