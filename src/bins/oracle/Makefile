CUR_SRC_DIR=${CURDIR}

include ${ROOT_DIR}/helpers.mk
include ${ROOT_DIR}/products.mk

all: oracle_client oracle_server

.PHONY: oracle_client
oracle_client: ${CUR_BUILD_DIR}/client

.PHONY: oracle_server
oracle_server: ${CUR_BUILD_DIR}/server

deps=${Protos_lib} ${Protos_hdrs} \
	 ${Oracle_lib} ${Oracle_hdrs} \
	 ${Graph_lib} ${Graph_hdrs} \
	 ${Input_lib} ${Input_hdrs}

${CUR_BUILD_DIR}/client: client_main.cpp ${deps} | ${CUR_BUILD_DIR}
	${CXX} ${CXXFLAGS} -o $@ client_main.cpp \
		-L${BUILD_DIR}/protos -lprotos \
		-L${BUILD_DIR}/oracle -loracle \
		-L${BUILD_DIR}/graphsource -lsources \
		-L${BUILD_DIR}/graph -lgraph \
		${LDFLAGS}

${CUR_BUILD_DIR}/server: server_main.cpp server.cpp ${deps} | ${CUR_BUILD_DIR}
	${CXX} ${CXXFLAGS} -o $@ server_main.cpp server.cpp \
		-L${BUILD_DIR}/protos -lprotos \
		-L${BUILD_DIR}/oracle -loracle \
		-L${BUILD_DIR}/graphsource -lsources \
		-L${BUILD_DIR}/graph -lgraph \
		${LDFLAGS}

# Misc
.PHONY: clangformat
clangformat: ${CPP_SRCS} ${CPP_HDRS}
	${CLANGFORMAT} $^
