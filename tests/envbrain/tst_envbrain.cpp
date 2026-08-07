#include <QtTest/QtTest>
#include "envbrain.h"
#include "ui/worldmodel.h"

// ---------------------------------------------------------------------------
// Component test: EnvBrain + a real WorldModel, wired together the same way
// mainwindow.cpp does (EnvBrain(&wm)), but with no camera/timers driving it.
// Covers the pure point-generation helpers used to seed experiments
// (makeGridPoints/makeStarPoints) -- currently only ever exercised visually.
// ---------------------------------------------------------------------------
class TestEnvBrain : public QObject {
    Q_OBJECT
private slots:

    void makeGridPoints_returnsRowsTimesColsPoints() {
        WorldModel wm;
        EnvBrain env(&wm);

        QList<QPoint> pts = env.makeGridPoints(2, 3, 10, 20, QPoint(5, 5));
        QCOMPARE(pts.size(), 2 * 3);
        QCOMPARE(pts.first(), QPoint(5, 5));   // i=0, j=0
        QCOMPARE(pts.last(), QPoint(25, 25));  // i=nCols-1=2, j=nRows-1=1
    }

    void makeGridPoints_singleCell_isJustOrigin() {
        WorldModel wm;
        EnvBrain env(&wm);

        QList<QPoint> pts = env.makeGridPoints(1, 1, 10, 10, QPoint(3, 4));
        QCOMPARE(pts.size(), 1);
        QCOMPARE(pts.first(), QPoint(3, 4));
    }

    void makeStarPoints_returnsArmsTimesLayersPoints() {
        WorldModel wm;
        EnvBrain env(&wm);

        QList<QPoint> pts = env.makeStarPoints(4, 3, 10, QPoint(0, 0));
        QCOMPARE(pts.size(), 4 * 3);
        // Arm 0 sits at theta=0, so its points land exactly on the x-axis.
        QCOMPARE(pts.first(), QPoint(10, 0));  // arm 0, layer 1
        QCOMPARE(pts.at(1), QPoint(20, 0));    // arm 0, layer 2
    }
};

QTEST_MAIN(TestEnvBrain)
#include "tst_envbrain.moc"
