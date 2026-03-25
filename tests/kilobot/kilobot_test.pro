QT += testlib core
CONFIG += qt warn_on testcase
TEMPLATE = app
TARGET = tst_kilobot

INCLUDEPATH += ../../
INCLUDEPATH += /usr/local/include/opencv4

LIBS += -L/usr/local/lib \
        -lopencv_core

SOURCES += tst_kilobot.cpp \
           ../../Kilobot/kilobot.cpp

HEADERS += ../../Kilobot/kilobot.h
