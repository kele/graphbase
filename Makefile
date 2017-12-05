export SRC_DIR?=${CURDIR}/src
export BUILD_DIR?=${CURDIR}/build

# Necessary for all the Makefiles to work
export ROOT_DIR=${CURDIR}

# Some defaults
export CXX ?= clang++
export CXXFLAGS_DEBUG = -O0 -DDEBUG -g -ggdb
export CXXFLAGS ?= -Wall -pedantic -std=c++17 ${CXXFLAGS_DEBUG}

# Project specific
export LDFLAGS = -L/usr/local/lib `pkg-config --libs protobuf grpc++` \
	-Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed \
    -ldl \
	-lpthread

# estd is a handy extension to std used throughout the whole codebase
export ESTD_HDRS=$(wildcard ${SRC_DIR}/estd/*.hpp)

export CLANGFORMAT=clangformat -style=Google -i -sort-includes

# Build dir in include path is needed because of generated protos
export CXXFLAGS+= -I${SRC_DIR} -I${BUILD_DIR}

# Targets

all: graphbase test

.PHONY: graphbase
graphbase:
	${MAKE} -C ${SRC_DIR}/graph all
	${MAKE} -C ${SRC_DIR}/protos all
	${MAKE} -C ${SRC_DIR}/oracle all
	${MAKE} -C ${SRC_DIR}/graphsource all
	${MAKE} -C ${SRC_DIR}/bins/oracle all

.PHONY: clangformat
clangformat:
	${MAKE} -C ${SRC_DIR}/graph clangformat
	${MAKE} -C ${SRC_DIR}/oracle clangformat
	${MAKE} -C ${SRC_DIR}/graphsource clangformat
	${MAKE} -C ${SRC_DIR}/tst/graph clangformat
	${MAKE} -C ${SRC_DIR}/bins/oracle clangformat

.PHONY: test
test:
	${MAKE} -C ${SRC_DIR}/tst/graph test_all

run_test: test
	${BUILD_DIR}/tst/graph/test_all
	echo "All tests passed"
.PHONY: run_test

clean:
	rm -rf ${BUILD_DIR}
