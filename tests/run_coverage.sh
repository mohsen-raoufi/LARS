#!/bin/bash
# Build every tests/*/tst_* binary with gcov instrumentation, run them all,
# then turn the resulting .gcda files into a coverage report via gcovr
# (Cobertura XML for CI/Codecov, HTML for humans).
set -e
cd "$(dirname "$0")"

qmake
make -j"$(nproc 2>/dev/null || sysctl -n hw.ncpu)"

# A couple of tests build against QtGui (QColor/QBrush); on a headless CI
# runner there's no X11 display, so force Qt's built-in headless platform
# plugin instead of trying (and aborting) on xcb.
export QT_QPA_PLATFORM=offscreen

status=0
for f in */tst_*; do
    [ -x "$f" ] || continue
    echo "== $f =="
    ./"$f" || status=1
done

mkdir -p coverage_html
gcovr --root .. \
      --filter '.*/(Kilobot|ohc|ui)/.*' \
      --filter '.*/envbrain\.(cpp|h)' \
      --exclude-unreachable-branches \
      --print-summary \
      --xml-pretty -o coverage.xml \
      --html --html-details -o coverage_html/index.html \
      .

exit $status
