CUR_SRC_DIR=${CURDIR}

include ${ROOT_DIR}/helpers.mk
include ${ROOT_DIR}/products.mk

all: ${Protos_lib} ${Protos_hdrs}

# Library
protos=$(wildcard *.proto)
proto_grpc_objects=$(patsubst %.proto,${CUR_BUILD_DIR}/%.grpc.pb.o, ${protos})
proto_objects=$(patsubst %.proto,${CUR_BUILD_DIR}/%.pb.o, ${protos})

${Protos_lib}: ${proto_objects} ${proto_grpc_objects} ${Protos_hdrs} | ${CUR_BUILD_DIR}
	ar rcs libprotos.a ${proto_objects} ${proto_grpc_objects}
	mv libprotos.a $@

# Headers
hdrs=$(wildcard ${BUILD_DIR}/protos/%.pb.h) $(wildcard ${BUILD_DIR}/protos/%.grpc.pb.h)

${Protos_hdrs}: ${hdrs}
	touch ${Protos_hdrs}

# Build rules
# Prevent deleting the generated .cc and .h files. They might be useful for gdb.
.PRECIOUS: ${CUR_BUILD_DIR}/%.grpc.pb.h ${CUR_BUILD_DIR}/%.grpc.pb.cc

${CUR_BUILD_DIR}/%.grpc.pb.h ${CUR_BUILD_DIR}/%.grpc.pb.cc: %.proto | ${CUR_BUILD_DIR}
	protoc -I. \
		--grpc_out=${CUR_BUILD_DIR} \
		--plugin=protoc-gen-grpc=`which grpc_cpp_plugin` \
		$^

# Prevent deleting the generated .cc and .h files. They might be useful for gdb.
.PRECIOUS: ${CUR_BUILD_DIR}/%.pb.h ${CUR_BUILD_DIR}/%.pb.cc

${CUR_BUILD_DIR}/%.pb.h ${CUR_BUILD_DIR}/%.pb.cc: %.proto | ${CUR_BUILD_DIR}
	protoc -I. \
		--cpp_out=${CUR_BUILD_DIR} \
		$^

