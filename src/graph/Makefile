CUR_SRC_DIR=${CURDIR}

include ${ROOT_DIR}/helpers.mk
include ${ROOT_DIR}/products.mk

all: ${Graph_lib} ${Graph_hdrs}

# common/
common_src_dir=${CUR_SRC_DIR}/common
common_build_dir=${CUR_BUILD_DIR}/common
common_srcs=$(wildcard ${common_src_dir}/*.cpp)
common_hdrs=$(wildcard ${common_src_dir}/*.hpp)
common_objs=$(patsubst ${common_src_dir}/%.cpp,${common_build_dir}/%.o,${common_srcs})

${common_build_dir}:
	mkdir -p ${common_build_dir}

${common_build_dir}/%.o: ${common_src_dir}/%.cpp ${ESTD_HDRS} ${common_src_dir}/%.hpp | ${common_build_dir}
	${CXX} ${CXXFLAGS} -c -o $@ $<

# graph/
graph_src_dir=${CUR_SRC_DIR}/graph
graph_build_dir=${CUR_BUILD_DIR}/graph
graph_srcs=$(wildcard ${graph_src_dir}/*.cpp)
graph_hdrs=$(wildcard ${graph_src_dir}/*.hpp)
graph_objs=$(patsubst ${graph_src_dir}/%.cpp,${graph_build_dir}/%.o,${graph_srcs})

${graph_build_dir}:
	mkdir -p ${graph_build_dir}

${graph_build_dir}/%.o: ${graph_src_dir}/%.cpp ${ESTD_HDRS} ${graph_src_dir}/%.hpp | ${graph_build_dir}
	${CXX} ${CXXFLAGS} -c -o $@ $<

# algo/
algo_src_dir=${CUR_SRC_DIR}/algo
algo_build_dir=${CUR_BUILD_DIR}/algo
algo_srcs=$(wildcard ${algo_src_dir}/*.cpp)
algo_hdrs=$(wildcard ${algo_src_dir}/*.hpp)
algo_objs=$(patsubst ${algo_src_dir}/%.cpp,${algo_build_dir}/%.o,${algo_srcs})

${algo_build_dir}:
	mkdir -p ${algo_build_dir}

${algo_build_dir}/%.o: ${algo_src_dir}/%.cpp ${ESTD_HDRS} ${algo_src_dir}/%.hpp | ${algo_build_dir}
	${CXX} ${CXXFLAGS} -c -o $@ $<

# Combined
objs=${graph_objs} ${common_objs} ${algo_objs}

srcs=${graph_srcs} ${common_srcs} ${algo_srcs}
hdrs=${graph_hdrs} ${common_hdrs} ${algo_hdrs}

# Headers
${Graph_hdrs}: ${hdrs}
	touch $@

# Library
${Graph_lib}: ${objs} ${ESTD_HDRS} | ${CUR_BUILD_DIR}
	ar rcs libgraph.a ${objs}
	mv libgraph.a $@

# Misc
.PHONY: clangformat
clangformat: ${srcs} ${hdrs}
	${CLANGFORMAT} $^
