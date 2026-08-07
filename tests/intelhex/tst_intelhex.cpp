#include <QtTest/QtTest>
#include <sstream>
#include <iterator>
#include "ohc/intelhex.h"

// ---------------------------------------------------------------------------
// intelhex::hex_data — Intel INHX8M parser used by the firmware upload path
// (SerialConnection::sendProgram). No coverage existed for this before.
//
// Records below are genuine INHX8M lines (":LLAAAATT<data><checksum>") with
// checksums computed by hand so hex_data::read() actually accepts them —
// read() silently stops parsing on the first bad checksum, so a wrong
// checksum here would make these tests pass for the wrong reason.
// ---------------------------------------------------------------------------
class TestIntelHex : public QObject {
    Q_OBJECT
private slots:

    void read_singleDataRecord_populatesBytes() {
        // :04 0000 00 DEADBEEF C4  -> 4 bytes at address 0
        std::istringstream iss(":04000000DEADBEEFC4\n:00000001FF\n");
        intelhex::hex_data hex;
        hex.read(iss);

        QCOMPARE(hex.size(), (intelhex::hex_data::size_type)4);
        QCOMPARE(hex.min_address(), (intelhex::address_type)0);
        QCOMPARE(hex.max_address(), (intelhex::address_type)3);
        QCOMPARE(hex.get(0), (intelhex::value_type)0xDE);
        QCOMPARE(hex.get(1), (intelhex::value_type)0xAD);
        QCOMPARE(hex.get(2), (intelhex::value_type)0xBE);
        QCOMPARE(hex.get(3), (intelhex::value_type)0xEF);
    }

    void get_unsetAddress_returnsFill() {
        std::istringstream iss(":04000000DEADBEEFC4\n:00000001FF\n");
        intelhex::hex_data hex;
        hex.read(iss);

        // Default fill value is 0; address 100 was never written.
        QCOMPARE(hex.get(100), (intelhex::value_type)0);
    }

    void badChecksum_stopsParsingEarly() {
        // Same record with the last byte corrupted (C4 -> C5).
        std::istringstream iss(":04000000DEADBEEFC5\n:00000001FF\n");
        intelhex::hex_data hex;
        hex.read(iss);

        // read() bails out on the first bad checksum, so nothing was stored.
        QCOMPARE(hex.size(), (intelhex::hex_data::size_type)0);
    }

    void set_then_erase_roundtrips() {
        intelhex::hex_data hex;
        hex.set(10, 0x42);
        QCOMPARE(hex.get(10), (intelhex::value_type)0x42);

        hex.erase(10);
        QCOMPARE(hex.get(10), (intelhex::value_type)0); // back to fill value
    }

    void compact_mergesAdjacentBlocks() {
        // Two separate 4-byte records, contiguous (0..3 and 4..7): read()
        // does NOT merge them into one map entry on its own, that's what
        // compact() is for.
        std::istringstream iss(
            ":04000000DEADBEEFC4\n"
            ":04000400112233444E\n"
            ":00000001FF\n");
        intelhex::hex_data hex;
        hex.read(iss);

        QCOMPARE(hex.size(), (intelhex::hex_data::size_type)8);
        QCOMPARE(std::distance(hex.begin(), hex.end()), (std::ptrdiff_t)2);

        hex.compact();

        QCOMPARE(std::distance(hex.begin(), hex.end()), (std::ptrdiff_t)1);
        QCOMPARE(hex.size(), (intelhex::hex_data::size_type)8);
        QCOMPARE(hex.min_address(), (intelhex::address_type)0);
        QCOMPARE(hex.max_address(), (intelhex::address_type)7);
        // Data survives the merge.
        QCOMPARE(hex.get(0), (intelhex::value_type)0xDE);
        QCOMPARE(hex.get(4), (intelhex::value_type)0x11);
        QCOMPARE(hex.get(7), (intelhex::value_type)0x44);
    }

    void clear_emptiesContainer() {
        intelhex::hex_data hex;
        hex.set(0, 0x01);
        hex.clear();
        QCOMPARE(hex.size(), (intelhex::hex_data::size_type)0);
    }
};

QTEST_APPLESS_MAIN(TestIntelHex)
#include "tst_intelhex.moc"
