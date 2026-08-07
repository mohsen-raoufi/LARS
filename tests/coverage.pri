# Shared gcov instrumentation for every test target.
# Included from each tests/*/*.pro via `include(../coverage.pri)`.
QMAKE_CXXFLAGS += --coverage -O0 -g
QMAKE_LFLAGS   += --coverage
LIBS           += -lgcov
