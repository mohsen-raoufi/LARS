#include <QtTest/QtTest>
#include "ui/geom/voronoiGenerator.h"

// ---------------------------------------------------------------------------
// voronoiGenerator — this is the only file under ui/geom/ that's actually
// compiled (LARS.pro comments out the rest of that directory; the rest is a
// dead vendored RCSC geometry lib). Used from ui/renderarea.cpp to draw the
// Voronoi tessellation over the tracked robots. These are its plain
// point-in/point-out geometry helpers.
// ---------------------------------------------------------------------------
class TestVoronoiGenerator : public QObject {
    Q_OBJECT
private slots:

    void findIntersection_rightward_hitsRightEdge() {
        QLineF line(QPointF(50, 50), QPointF(150, 50));
        QPoint result = voronoiGenerator::findIntersection(line, 0, 0, 100, 100);
        QCOMPARE(result, QPoint(100, 50));
    }

    void findIntersection_leftward_hitsLeftEdge() {
        QLineF line(QPointF(50, 50), QPointF(-50, 50));
        QPoint result = voronoiGenerator::findIntersection(line, 0, 0, 100, 100);
        QCOMPARE(result, QPoint(0, 50));
    }

    void findIntersection_segmentOutsideRect_returnsDefault() {
        QLineF line(QPointF(200, 200), QPointF(300, 300));
        QPoint result = voronoiGenerator::findIntersection(line, 0, 0, 100, 100);
        QCOMPARE(result, QPoint(0, 0));
    }

    void calculateIntersection_pointingRight_hitsRightBoundary() {
        voronoiGenerator gen;
        QRectF bounds(0, 0, 100, 100);
        QPointF result = gen.calculateIntersection(QPointF(50, 50), QPointF(1, 0), bounds);
        QCOMPARE(result, QPointF(100, 50));
    }

    void calculateIntersectionII_pointingRight_hitsRightBoundary() {
        voronoiGenerator gen;
        QRectF bounds(0, 0, 100, 100);
        QPointF result = gen.calculateIntersectionII(QPointF(50, 50), QPointF(75, 50), bounds);
        QCOMPARE(result, QPointF(100, 50));
    }

    void calculateIntersectionII_zeroLengthDirection_returnsMidPoint() {
        voronoiGenerator gen;
        QRectF bounds(0, 0, 100, 100);
        QPointF result = gen.calculateIntersectionII(QPointF(20, 20), QPointF(20, 20), bounds);
        QCOMPARE(result, QPointF(20, 20));
    }

    void generateVoronoi_oneCellPerSite() {
        QList<QPoint> points = {QPoint(0, 0), QPoint(10, 0), QPoint(0, 10)};
        boost::polygon::voronoi_diagram<double> vd;
        voronoiGenerator::generateVoronoi(points, vd);
        QCOMPARE((int)vd.num_cells(), points.size());
    }
};

QTEST_APPLESS_MAIN(TestVoronoiGenerator)
#include "tst_voronoigenerator.moc"
