QT += testlib core
CONFIG += qt warn_on testcase
TEMPLATE = app
TARGET = tst_kilobot

INCLUDEPATH += ../../

# Resolved via pkg-config instead of a hardcoded path: OpenCV lands in
# different places depending on how it was installed (apt: /usr/include,
# Homebrew: /opt/homebrew, source build on Jetson: /usr/local).
CONFIG += link_pkgconfig
PKGCONFIG += opencv4

SOURCES += tst_kilobot.cpp \
           ../../Kilobot/kilobot.cpp

HEADERS += ../../Kilobot/kilobot.h

include(../coverage.pri)
