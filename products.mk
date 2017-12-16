# estd
# This is kept simple as it doesn't require any building rules.
export Estd_hdrs=$(wildcard ${SRC_DIR}/estd/*.hpp)

# protos
export Protos_lib=${BUILD_DIR}/protos/libprotos.a
export Protos_hdrs=${BUILD_DIR}/protos/_headers

${Protos_lib}:
	${MAKE} -C ${SRC_DIR}/protos ${Protos_lib}

${Protos_hdrs}:
	${MAKE} -C ${SRC_DIR}/protos ${Protos_hdrs}

# graph
export Graph_lib=${BUILD_DIR}/graph/libgraph.a
export Graph_hdrs=${BUILD_DIR}/graph/_headers

${Graph_lib}:
	${MAKE} -C ${SRC_DIR}/graph ${Graph_lib}

${Graph_hdrs}:
	${MAKE} -C ${SRC_DIR}/graph ${Graph_hdrs}

# oracle
export Oracle_lib=${BUILD_DIR}/oracle/liboracle.a
export Oracle_hdrs=${BUILD_DIR}/oracle/_headers

${Oracle_lib}:
	${MAKE} -C ${SRC_DIR}/oracle ${Oracle_lib}

${Oracle_hdrs}:
	${MAKE} -C ${SRC_DIR}/oracle ${Oracle_hdrs}

# graphsource
export Sources_lib=${BUILD_DIR}/graphsource/libsources.a
export Sources_hdrs=${BUILD_DIR}/graphsource/_headers

${Sources_lib}:
	${MAKE} -C ${SRC_DIR}/graphsource ${Sources_lib}

${Sources_hdrs}:
	${MAKE} -C ${SRC_DIR}/graphsource ${Sources_hdrs}

# conversions
export Conversions_lib=${BUILD_DIR}/conversions/libconversions.a
export Conversions_hdrs=${BUILD_DIR}/conversions/_headers

${Conversions_lib}:
	${MAKE} -C ${SRC_DIR}/conversions ${Conversions_lib}

${Conversions_hdrs}:
	${MAKE} -C ${SRC_DIR}/conversions ${Conversions_hdrs}
