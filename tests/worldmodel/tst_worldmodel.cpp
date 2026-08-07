#include <QtTest/QtTest>
#include "ui/worldmodel.h"

// ---------------------------------------------------------------------------
// WorldModel — the shared arena/state container every subsystem reads from.
// It has no behaviour beyond a handful of setters and derived-geometry
// fields computed in its constructor; those derived fields (marker1..3,
// expFieldRect) are currently only checked by eyeballing the projected
// arena on screen. Built with DEFINES += FOR_KILOBOT to match LARS.pro's
// default configuration.
// ---------------------------------------------------------------------------
class TestWorldModel : public QObject {
    Q_OBJECT
private slots:

    void markers_areDerivedFromMarker0AndArenaSize() {
        WorldModel wm;
        QCOMPARE(wm.marker1_pos, wm.marker0_pos + QPoint(0, wm.arenaHeight));
        QCOMPARE(wm.marker2_pos, wm.marker0_pos + QPoint(wm.arenaWidth, 0));
        QCOMPARE(wm.marker3_pos, wm.marker0_pos + QPoint(wm.arenaWidth, wm.arenaHeight));
        QCOMPARE(wm.marker0_BR, wm.marker0_pos + QPoint(wm.marker_length, wm.marker_length));
    }

    void expFieldRect_spansMarker0ToMarker3() {
        WorldModel wm;
        QRect expected(wm.marker0_pos + QPoint(wm.marker_length, wm.marker_length), wm.marker3_pos);
        QCOMPARE(wm.expFieldRect, expected);
    }

    void setFieldSize_updatesFieldSize() {
        WorldModel wm;
        wm.setFieldSize(QSize(42, 24));
        QCOMPARE(wm.fieldSize, QSize(42, 24));
    }

    void setFieldColor_updatesFieldCol() {
        WorldModel wm;
        wm.setFieldColor(QColor(10, 20, 30));
        QCOMPARE(wm.fieldCol, QColor(10, 20, 30));
    }

    void setFieldColorHSV_convertsToRGB() {
        WorldModel wm;
        wm.setFieldColorHSV(0, 0, 255); // pure white in HSV
        QCOMPARE(wm.fieldCol, QColor::fromHsv(0, 0, 255));
    }

    void setRobotCustomColor_updatesBrush() {
        WorldModel wm;
        wm.setRobotCustomColor(QColor(1, 2, 3));
        QCOMPARE(wm.brush_robotCustom_0->color(), QColor(1, 2, 3));
    }

    void setNullRobotCustomBrush_togglesFlag() {
        WorldModel wm;
        QVERIFY(!wm.boolNullBrushForRobots);
        wm.setNullRobotCustomBrush(true);
        QVERIFY(wm.boolNullBrushForRobots);
    }
};

QTEST_MAIN(TestWorldModel)
#include "tst_worldmodel.moc"
