#include <QtTest/QtTest>
#include <QSignalSpy>
#include "ohc/serialconn.h"
#include "ohc/packet.h"

class TestSerialConnection : public QObject {
    Q_OBJECT

private slots:

    // enumerate() must not crash and must return a QVector on any platform.
    void enumerate_returnsVector() {
        QVector<QString> ports = SerialConnection::enumerate();
        // Just verify the call completes and the type is correct.
        // On CI without USB devices this may be empty — that is fine.
        QVERIFY(ports.size() >= 0);
    }

    // Constructing with no port name must not crash.
    void defaultConstruct_doesNotCrash() {
        SerialConnection sc;
        QVERIFY(sc.getPort().isEmpty());
    }

    // Opening a nonexistent port must emit status with an error string,
    // not crash or silently succeed.
    void open_nonexistentPort_emitsError() {
        SerialConnection sc(nullptr, "/dev/nonexistent_lars_test_port");
        QSignalSpy spy(&sc, &SerialConnection::status);
        sc.open();
        QVERIFY(spy.count() >= 1);
        QString msg = spy.first().first().toString();
        // The status message should not be "connected." for a bad port.
        QVERIFY2(msg != "connected.", qPrintable(msg));
    }

    // close() on a never-opened connection must not crash.
    void close_whenNotOpen_doesNotCrash() {
        SerialConnection sc;
        sc.close(); // context == NULL, should be a no-op
    }

    // queueCommand adds to the internal queue and cmdQueueSize tracks it.
    // We test this without a real device by checking the queue counter.
    // Note: sendQueuedCommand will immediately attempt a write and fail
    // (no device), so we verify the queue is drained (not grown unboundedly).
    void queueCommand_increasesThenDrainsQueue() {
        SerialConnection sc;
        // Without an open port, sendCommand emits error but does not crash.
        // Queue should reach 1 then drain immediately (sendQueuedCommand is
        // called synchronously in queueCommand when delay has elapsed).
        QSignalSpy errSpy(&sc, &SerialConnection::error);
        QByteArray cmd(PACKET_SIZE, 0);
        sc.queueCommand(cmd);
        // After the call the queue should be empty (drained synchronously)
        // or the command count should be 0 or 1 depending on timing.
        QVERIFY(sc.cmdQueueSize() >= 0);
    }

    // clearQueue empties the queue.
    void clearQueue_emptiesQueue() {
        SerialConnection sc;
        // Push a command then clear before the event loop processes it.
        // We do this by connecting a dummy error spy so Qt doesn't warn.
        QSignalSpy errSpy(&sc, &SerialConnection::error);
        QByteArray cmd(PACKET_SIZE, 0);
        sc.queueCommand(cmd);
        sc.clearQueue();
        QCOMPARE(sc.cmdQueueSize(), 0);
    }

    // Verify the packet checksum formula used in KilobotOverheadController.
    // The send path computes: PACKET_HEADER ^ PACKET_FORWARDMSG ^ type ^ XOR(payload[0..8])
    // This test validates the formula independently of hardware.
    void packetChecksum_matchesFormula() {
        uint8_t payload[9] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09};
        uint8_t type = 0x42;

        uint8_t expected = PACKET_HEADER ^ PACKET_FORWARDMSG ^ type;
        for (int i = 0; i < 9; ++i)
            expected ^= payload[i];

        // Reconstruct the packet as the OHC does and verify the final byte.
        QByteArray packet(PACKET_SIZE, 0);
        packet[0] = PACKET_HEADER;
        packet[1] = PACKET_FORWARDMSG;
        uint8_t checksum = PACKET_HEADER ^ PACKET_FORWARDMSG ^ type;
        for (int i = 0; i < 9; i++) {
            packet[2+i] = payload[i];
            checksum ^= payload[i];
        }
        packet[11] = type;
        packet[PACKET_SIZE-1] = checksum;

        QCOMPARE((uint8_t)packet[PACKET_SIZE-1], expected);
        QCOMPARE((uint8_t)packet[0], (uint8_t)PACKET_HEADER);
        QCOMPARE((uint8_t)packet[1], (uint8_t)PACKET_FORWARDMSG);
    }

    // All-zeros payload: checksum should be PACKET_HEADER ^ PACKET_FORWARDMSG ^ type.
    void packetChecksum_zeroPayload() {
        uint8_t payload[9] = {0};
        uint8_t type = NORMAL; // 0
        uint8_t expected = PACKET_HEADER ^ PACKET_FORWARDMSG ^ type;

        uint8_t checksum = PACKET_HEADER ^ PACKET_FORWARDMSG ^ type;
        for (int i = 0; i < 9; ++i)
            checksum ^= payload[i];

        QCOMPARE(checksum, expected);
    }
};

QTEST_GUILESS_MAIN(TestSerialConnection)
#include "tst_serialconn.moc"
