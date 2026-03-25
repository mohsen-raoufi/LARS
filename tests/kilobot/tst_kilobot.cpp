#include <QtTest/QtTest>
#include "Kilobot/kilobot.h"

// ---------------------------------------------------------------------------
// ColourBuffer tests
// ---------------------------------------------------------------------------
class TestColourBuffer : public QObject {
    Q_OBJECT
private slots:

    void freshBuffer_returnsOff() {
        // A newly constructed buffer fills with default-initialised lightColour
        // (value 0 == OFF). getAvgColour() should return OFF without any adds.
        ColourBuffer buf(5);
        QCOMPARE(buf.getAvgColour(), OFF);
    }

    void allSameColour_returnsIt() {
        ColourBuffer buf(4);
        buf.addColour(BLUE);
        buf.addColour(BLUE);
        buf.addColour(BLUE);
        buf.addColour(BLUE);
        QCOMPARE(buf.getAvgColour(), BLUE);
    }

    void majorityColour_wins() {
        // Buffer(5) starts as [OFF,OFF,OFF,OFF,OFF].
        // After 5 adds: [RED,RED,RED,GREEN,GREEN] — RED majority.
        ColourBuffer buf(5);
        buf.addColour(RED);
        buf.addColour(RED);
        buf.addColour(RED);
        buf.addColour(GREEN);
        buf.addColour(GREEN);
        QCOMPARE(buf.getAvgColour(), RED);
    }

    void bufferCycling_evictsOldest() {
        // Buffer(3) starts [OFF,OFF,OFF].
        // Fill with RED: [RED,RED,RED] -> RED wins.
        ColourBuffer buf(3);
        buf.addColour(RED);
        buf.addColour(RED);
        buf.addColour(RED);
        QCOMPARE(buf.getAvgColour(), RED);

        // Now push two GREENs: [RED,GREEN,GREEN] -> GREEN wins.
        buf.addColour(GREEN);
        buf.addColour(GREEN);
        QCOMPARE(buf.getAvgColour(), GREEN);
    }

    void sizeOneBuffer_lastWriteWins() {
        ColourBuffer buf(1);
        buf.addColour(BLUE);
        QCOMPARE(buf.getAvgColour(), BLUE);
        buf.addColour(RED);
        QCOMPARE(buf.getAvgColour(), RED);
    }
};

// ---------------------------------------------------------------------------
// Kilobot tests
// ---------------------------------------------------------------------------
class TestKilobot : public QObject {
    Q_OBJECT
private slots:

    void copyConstructor_preservesAllFields() {
        Kilobot a(42, QPointF(1.0, 2.0), QPointF(3.0, 4.0), GREEN);
        Kilobot b(a);
        QCOMPARE(b.getID(),       (kilobot_id)42);
        QCOMPARE(b.getPosition(), QPointF(1.0, 2.0));
        QCOMPARE(b.getVelocity(), QPointF(3.0, 4.0));
        QCOMPARE(b.getLedColour(), GREEN);
    }

    void setID_getID_roundtrip() {
        Kilobot k(1, QPointF(0,0), QPointF(0,0), OFF);
        k.setID(99);
        QCOMPARE(k.getID(), (kilobot_id)99);
    }

    void unassignedID_roundtrip() {
        Kilobot k(1, QPointF(0,0), QPointF(0,0), OFF);
        k.setID(UNASSIGNED_ID);
        QCOMPARE(k.getID(), (kilobot_id)UNASSIGNED_ID);
    }

    void updateState_changesAllThreeFields() {
        Kilobot k(1, QPointF(0,0), QPointF(0,0), OFF);
        k.updateState(QPointF(5.0, 6.0), QPointF(7.0, 8.0), RED);
        QCOMPARE(k.getPosition(),  QPointF(5.0, 6.0));
        QCOMPARE(k.getVelocity(),  QPointF(7.0, 8.0));
        QCOMPARE(k.getLedColour(), RED);
    }

    void defaultConstructor_hasUnassignedID() {
        Kilobot k;
        QCOMPARE(k.getID(), (kilobot_id)UNASSIGNED_ID);
    }
};

// ---------------------------------------------------------------------------
// Run both suites from one binary
// ---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    int status = 0;
    {
        TestColourBuffer t;
        status |= QTest::qExec(&t, argc, argv);
    }
    {
        TestKilobot t;
        status |= QTest::qExec(&t, argc, argv);
    }
    return status;
}

#include "tst_kilobot.moc"
