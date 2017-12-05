ifndef SRC_DIR
	$(error "The SRC_DIR variable needs to be set for sub-makes,")
endif

ifndef BUILD_DIR
	$(error "The BUILD_DIR variable needs to be set for sub-makes.")
endif

CUR_BUILD_DIR=$(patsubst ${SRC_DIR}%,${BUILD_DIR}%,${CUR_SRC_DIR})

${CUR_BUILD_DIR}:
	mkdir -p ${CUR_BUILD_DIR}

.PHONY: clean
clean:
	rm -rf ${CUR_BUILD_DIR}

# Default .o building from cpp files
${CUR_BUILD_DIR}/%.o: ${CUR_SRC_DIR}/%.cpp ${CUR_SRC_DIR}/%.hpp | ${CUR_BUILD_DIR}
	${CXX} ${CXXFLAGS} -c -o $@ $<

CPP_SRCS=$(wildcard *.cpp)
CPP_HDRS=$(wildcard *.hpp)
CPP_OBJECTS=$(patsubst %.cpp,${CUR_BUILD_DIR}/%.o,${CPP_SRCS})
