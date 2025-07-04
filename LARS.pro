DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x050F00
QT       += core gui
CONFIG += c++11

#QMAKE_LFLAGS += -Wl,-rpath,'lib'

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport quick

TARGET = LARS
TEMPLATE = app

DEFINES += USE_OPENCV3
DEFINES += USE_PYLON
DEFINES += USE_CUDA
DEFINES += FOR_KILOBOT

INCLUDEPATH += /usr/local/include/opencv4
INCLUDEPATH += /usr/include/boost

LIBS += -L/usr/local/lib/ \
        -lopencv_core \
        -lopencv_imgproc \
        -lopencv_features2d \
        -lopencv_highgui \
        -lopencv_calib3d \
        -lopencv_objdetect \
        -lopencv_photo \
        -lopencv_stitching \
        -lopencv_flann \
        -lopencv_ml \
        -lopencv_objdetect  \
        -lopencv_photo \
        -lopencv_stitching \
        -lopencv_superres \
        -lopencv_video \
        -lopencv_videostab \
        -lopencv_videoio \
        -lopencv_imgcodecs \
        -lopencv_aruco \
        -lz \
        -ligraph

# CUDA
LIBS += -lopencv_cudawarping \
        -lopencv_cudafeatures2d \
        -lopencv_cudaimgproc \
        -lopencv_cudafilters \
        -lopencv_cudaarithm

# ZBAR for qr detection// Not necessary anymore!
LIBS += -lzbar


# Boost library for geometric calculations, inc. Voronoii
LIBS += -lboost_system

SOURCES += main.cpp\
    Kilobot/kilobot.cpp \
    Kilobot/kilobotoverheadcontroller.cpp \
    arenaWindow.cpp \
    envbrain.cpp \
    etc/publicvars.cpp \
    ohc/calibrate.cpp \
    ohc/intelhex.cpp \
    ohc/serialconn.cpp \
    ohc/serialwin.cpp \
    qcustomplot.cpp \
    mainwindow.cpp \
#    savevid_thread.cpp \
    savevidthread.cpp \
    tracker/detectQR.cpp \
#    tracker/kilobottracker_copy.cpp \
    tracker/pylon.cpp \
 \#    tracker/pylon_org.cpp
#    ui/geom/circle_2d.cpp \
#    ui/geom/composite_region_2d.cpp \
#    ui/geom/convex_hull.cpp \
#    ui/geom/delaunay_triangulation.cpp \
#    ui/geom/line_2d.cpp \
#    ui/geom/matrix_2d.cpp \
#    ui/geom/polygon_2d.cpp \
#    ui/geom/ray_2d.cpp \
#    ui/geom/rect_2d.cpp \
#    ui/geom/sector_2d.cpp \
#    ui/geom/segment_2d.cpp \
#    ui/geom/triangle_2d.cpp \
#    ui/geom/voronoi_diagram.cpp \
#    ui/mobileobject.cpp \
    tracker/robottracker.cpp \
    ui/geom/voronoiGenerator.cpp \
    ui/renderarea.cpp \
#    ui/robot.cpp \
    ui/worldmodel.cpp

HEADERS  += mainwindow.h \
    Kilobot/kilobot.h \
    Kilobot/kilobotenvironment.h \
    Kilobot/kilobotexperiment.h \
    Kilobot/kilobotoverheadcontroller.h \
    arenaWindow.h \
    envbrain.h \
    etc/publicvars.h \
    ohc/calibrate.h \
    ohc/intelhex.h \
    ohc/packet.h \
    ohc/serialconn.h \
    ohc/serialwin.h \
    qcustomplot.h \
#    savevid_thread.h \
    savevidthread.h \
    tracker/detectQR.h \
    tracker/kilobot.h \
#    tracker/kilobottracker_copy.h \
    tracker/pylon.h \
#    tracker/pylon_org.h
#    ui/geom/angle_deg.h \
#    ui/geom/circle_2d.h \
#    ui/geom/composite_region_2d.h \
#    ui/geom/convex_hull.h \
#    ui/geom/delaunay_triangulation.h \
#    ui/geom/geom.h \
#    ui/geom/line_2d.h \
#    ui/geom/matrix_2d.h \
#    ui/geom/polygon_2d.h \
#    ui/geom/ray_2d.h \
#    ui/geom/rect_2d.h \
#    ui/geom/region_2d.h \
#    ui/geom/sector_2d.h \
#    ui/geom/segment_2d.h \
#    ui/geom/size_2d.h \
#    ui/geom/triangle_2d.h \
#    ui/geom/triangulation.h \
#    ui/geom/vector_2d.h \
#    ui/geom/voronoi_diagram.h \
#    ui/mobileobject.h \
    tracker/robottracker.h \
    ui/geom/voronoiGenerator.h \
    ui/renderarea.h \
#    ui/robot.h \
    ui/worldmodel.h

FORMS    += mainwindow.ui \
    DynamicWidgets.ui \
    arenaWindow.ui

RESOURCES += \
    resources.qrc


LIBS += -L/opt/pylon/lib -lpylonbase -lpylonutility -lGenApi_gcc_v3_1_Basler_pylon -lGCBase_gcc_v3_1_Basler_pylon
INCLUDEPATH += /opt/pylon/include

#SOURCES += tracker/pylon.cpp
#HEADERS += tracker/pylon.h

#DISTFILES += \
#    Files/marker0.png \
#    Files/marker1.png \
#    Files/marker2.png \
#    Files/marker3.png

DISTFILES += \
    pyTestClass.py


