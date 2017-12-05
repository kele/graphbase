CUR_SRC_DIR=${CURDIR}

include ${ROOT_DIR}/helpers.mk
include ${ROOT_DIR}/products.mk

all: test_all

# graph/ tests
graph_tst_dir=${CUR_SRC_DIR}/graph
graph_tst_build_dir=${CUR_BUILD_DIR}/graph
graph_tst_srcs=$(wildcard ${graph_tst_dir}/*.cpp)
graph_tst_hdrs=$(wildcard ${graph_tst_dir}/*.hpp)
graph_tst_objects=$(patsubst ${graph_tst_dir}/%.cpp,${graph_tst_build_dir}/%.o,${graph_tst_srcs})

${graph_tst_build_dir}:
	mkdir -p ${graph_tst_build_dir}

# algo/ tests
algo_tst_dir=${CUR_SRC_DIR}/algo
algo_tst_build_dir=${CUR_BUILD_DIR}/algo
algo_tst_srcs=$(wildcard ${algo_tst_dir}/*.cpp)
algo_tst_hdrs=$(wildcard ${algo_tst_dir}/*.hpp)
algo_tst_objects=$(patsubst ${algo_tst_dir}/%.cpp,${algo_tst_build_dir}/%.o,${algo_tst_srcs})

${algo_tst_build_dir}:
	mkdir -p ${algo_tst_build_dir}


# Building
objs=${graph_tst_objects} ${algo_tst_objects}
deps=${Graph_lib} ${Graph_hdrs}

${CUR_BUILD_DIR}/test_all: ${CUR_SRC_DIR}/test_all.cpp ${objs} ${deps} | ${CUR_BUILD_DIR}
	${CXX} ${CXXFLAGS} -o $@ ${CUR_SRC_DIR}/test_all.cpp ${objs} \
		-L${BUILD_DIR}/graph -lgraph

${graph_tst_build_dir}/%.o: ${graph_tst_dir}/%.cpp ${ESTD_HDRS} ${Graph_hdrs} | ${graph_tst_build_dir}
	${CXX} ${CXXFLAGS} -c -o $@ $<

${algo_tst_build_dir}/%.o: ${algo_tst_dir}/%.cpp ${ESTD_HDRS} ${Graph_hdrs} | ${algo_tst_build_dir}
	${CXX} ${CXXFLAGS} -c -o $@ $<

# Targets
test_all: ${CUR_BUILD_DIR}/test_all
.PHONY: test_all

srcs=${graph_tst_srcs} ${algo_tst_srcs}
hdrs=${graph_tst_hdrs} ${algo_tst_hdrs}

clangformat: ${srcs} ${hdrs}
	${CLANGFORMAT} $^
.PHONY: clangformat
