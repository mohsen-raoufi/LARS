TEMPLATE = subdirs

# Each entry names the actual .pro file, not just the directory -- none of
# these share their directory's name (e.g. kilobot/kilobot_test.pro), and
# qmake's SUBDIRS only auto-derives "<dir>/<dir>.pro" without this.
SUBDIRS = \
    kilobot/kilobot_test.pro \
    serial/serial_test.pro \
    intelhex/tst_intelhex.pro \
    geom/tst_voronoigenerator.pro \
    worldmodel/tst_worldmodel.pro \
    kilobotoverheadcontroller/tst_koc.pro

# envbrain.h unconditionally includes opencv2/cudaarithm.hpp, so that test
# only builds where a CUDA-enabled OpenCV is available -- same requirement
# LARS.app itself already has. Skip it silently where that header is absent
# (e.g. plain apt/Homebrew OpenCV in CI) rather than failing the whole build.
exists(/usr/local/include/opencv4/opencv2/cudaarithm.hpp) | \
exists(/usr/include/opencv4/opencv2/cudaarithm.hpp) {
    SUBDIRS += envbrain/tst_envbrain.pro
} else {
    message("Skipping tests/envbrain: opencv2/cudaarithm.hpp not found (needs CUDA-enabled OpenCV)")
}
