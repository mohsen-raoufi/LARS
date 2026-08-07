TEMPLATE = subdirs
SUBDIRS = kilobot serial intelhex geom worldmodel kilobotoverheadcontroller

# envbrain.h unconditionally includes opencv2/cudaarithm.hpp, so that test
# only builds where a CUDA-enabled OpenCV is available -- same requirement
# LARS.app itself already has. Skip it silently where that header is absent
# (e.g. plain apt/Homebrew OpenCV in CI) rather than failing the whole build.
exists(/usr/local/include/opencv4/opencv2/cudaarithm.hpp) | \
exists(/usr/include/opencv4/opencv2/cudaarithm.hpp) {
    SUBDIRS += envbrain
} else {
    message("Skipping tests/envbrain: opencv2/cudaarithm.hpp not found (needs CUDA-enabled OpenCV)")
}
