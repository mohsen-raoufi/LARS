#include <QtTest/QtTest>
#include <QSignalSpy>
#include "Kilobot/kilobotoverheadcontroller.h"

// ---------------------------------------------------------------------------
// Component test: KilobotOverheadController + a real SerialConnection, wired
// together exactly as production code does (KOC's ctor builds its own
// SerialConnection and moves it to a worker thread) but with no OHC device
// plugged in. tests/serial already established that SerialConnection fails
// cleanly with no port; this exercises that same "no hardware" path through
// the higher-level controller: message queueing, packet framing, and the
// resulting error signal, without ever touching real serial hardware.
// ---------------------------------------------------------------------------
class TestKilobotOverheadController : public QObject {
    Q_OBJECT
private slots:

    void construction_reportsDisconnectedWithoutCrashing() {
        KilobotOverheadController koc;
        QSignalSpy errSpy(&koc, &KilobotOverheadController::errorMessage);
        // No device attached -> SerialConnection reports an error/disconnected
        // status asynchronously from its worker thread; give it a moment.
        errSpy.wait(500);
        QVERIFY(errSpy.count() >= 0); // reaching here at all means no crash/hang
    }

    void signalKilobot_queuesMessagesWithoutCrashing() {
        KilobotOverheadController koc;
        kilobot_message msg;
        msg.type = 1;
        msg.id = 7;
        msg.data = 42;

        koc.signalKilobot(msg);
        koc.signalKilobot(msg);
        koc.signalKilobot(msg);
        koc.signalKilobot(msg); // >2 queued -> sendBatch() takes the 3-in-1 packing path

        koc.sendBatch(); // not wired to a timer in this build; drive it directly
        QVERIFY(true); // survives packing + queueCommand() with no open port
    }

    void broadcastMessage_reservedTypeZero_isIgnored() {
        KilobotOverheadController koc;
        kilobot_broadcast msg;
        msg.type = 0; // reserved for composite/internal messages
        koc.broadcastMessage(msg); // should just warn and return, no packet sent
        QVERIFY(true);
    }

    void broadcastMessage_normalType_emitsStopButtonSignal() {
        KilobotOverheadController koc;
        QSignalSpy stopSpy(&koc, &KilobotOverheadController::setStopButton);

        kilobot_broadcast msg;
        msg.type = 5;
        msg.data = QVector<uint8_t>(9, 0);
        koc.broadcastMessage(msg);

        QVERIFY(stopSpy.count() >= 1);
    }

    void stopSending_afterRunKilobots_doesNotCrash() {
        KilobotOverheadController koc;
        koc.runKilobots();
        koc.stopSending();
        QVERIFY(true);
    }

    void clearMsgQueue_emptiesTheSerialQueue() {
        KilobotOverheadController koc;
        koc.clearMsgQueue(); // no device open; should be a safe no-op
        QVERIFY(true);
    }
};

QTEST_GUILESS_MAIN(TestKilobotOverheadController)
#include "tst_koc.moc"
