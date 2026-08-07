QT += testlib core gui
CONFIG += qt warn_on testcase
TEMPLATE = app
TARGET = tst_envbrain

# Same DEFINES/deps as LARS.pro. envbrain.h unconditionally pulls in
# opencv2/cudaarithm.hpp, so this target only builds where the main app
# would also build (CUDA-enabled OpenCV) -- see tests/tests.pro, which only
# adds this subdir when that header is actually found.
DEFINES += USE_OPENCV3
DEFINES += FOR_KILOBOT

INCLUDEPATH += ../../

# Resolved via pkg-config instead of hardcoded paths (see tests/kilobot/kilobot_test.pro).
CONFIG += link_pkgconfig
PKGCONFIG += opencv4 igraph

SOURCES += tst_envbrain.cpp \
           ../../envbrain.cpp \
           ../../ui/worldmodel.cpp

HEADERS += ../../envbrain.h \
           ../../ui/worldmodel.h

include(../coverage.pri)
