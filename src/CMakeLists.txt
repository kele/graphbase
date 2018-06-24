cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project("GraphBase")

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} --std=c++17)

set(GRPC_LIBS grpc grpc++ protobuf)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Proto compilation
set(PROTO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/protos)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/protos)
set(PROTO_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/protos)
set(PROTO_CPP_SRCS)
set(PROTO_CPP_HDRS)

file(GLOB PROTO_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/protos/*.proto)
foreach(PROTO_SRC ${PROTO_SRCS})
    get_filename_component(PROTO_SRC_ABS ${PROTO_SRC} ABSOLUTE)
    get_filename_component(PROTO_NAME ${PROTO_SRC} NAME_WE)

    add_custom_command(
        OUTPUT "${PROTO_OUTPUT_DIR}/${PROTO_NAME}.pb.cc"
            "${PROTO_OUTPUT_DIR}/${PROTO_NAME}.pb.h"
        COMMAND protoc
        ARGS -I${PROTO_DIR} --cpp_out=${PROTO_OUTPUT_DIR} ${PROTO_SRC_ABS}
        DEPENDS ${PROTO_SRC}
        COMMENT "Running proto compiler on ${PROTO_SRC}"
        VERBATIM)

    add_custom_command(
        OUTPUT "${PROTO_OUTPUT_DIR}/${PROTO_NAME}.grpc.pb.cc"
            "${PROTO_OUTPUT_DIR}/${PROTO_NAME}.grpc.pb.h"
        COMMAND protoc
        ARGS -I${PROTO_DIR} --grpc_out=${PROTO_OUTPUT_DIR} --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN} ${PROTO_SRC_ABS}
        DEPENDS ${PROTO_SRC}
        COMMENT "Running gRPC proto compiler on ${PROTO_SRC}"
        VERBATIM)

    # Protos
    list(APPEND PROTO_CPP_SRCS "${PROTO_OUTPUT_DIR}/${PROTO_NAME}.pb.cc")
    list(APPEND PROTO_CPP_HDRS "${PROTO_OUTPUT_DIR}/${PROTO_NAME}.pb.h")

    # gRPC
    list(APPEND PROTO_CPP_SRCS "${PROTO_OUTPUT_DIR}/${PROTO_NAME}.grpc.pb.cc")
    list(APPEND PROTO_CPP_HDRS "${PROTO_OUTPUT_DIR}/${PROTO_NAME}.grpc.pb.h")
endforeach()
set_source_files_properties(${PROTO_CPP_SRCS} ${PROTO_CPP_HDRS} PROPERTIES GENERATED TRUE)
add_library(ProtoLib ${PROTO_CPP_SRCS} ${PROTO_CPP_HDRS})
target_include_directories(ProtoLib PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

# Project sources
file(GLOB ESTD_HDRS ${CMAKE_CURRENT_SOURCE_DIR}/estd/*.hpp)

file(GLOB ALGO_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/graph/algo/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/graph/common/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/graph/graph/*.cpp
)
file(GLOB ALGO_HDRS
    ${CMAKE_CURRENT_SOURCE_DIR}/graph/algo/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/graph/common/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/graph/graph/*.hpp
)

file(GLOB CONVERSIONS_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/conversions/*.cpp)
file(GLOB CONVERSIONS_HDRS
    ${CMAKE_CURRENT_SOURCE_DIR}/conversions/*.hpp)

file(GLOB GRAPHSOURCE_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/graphsource/*.cpp)
file(GLOB GRAPHSOURCE_HDRS
    ${CMAKE_CURRENT_SOURCE_DIR}/graphsource/*.hpp)

file(GLOB ORACLE_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/oracle/*.cpp)
file(GLOB ORACLE_HDRS
    ${CMAKE_CURRENT_SOURCE_DIR}/oracle/*.hpp)

set(GRAPHBASE_LIB_SRCS
    ${ALGO_SRCS}
    ${CONVERSIONS_SRCS}
    ${GRAPHSOURCE_SRCS}
    ${ORACLE_SRCS}
)

set(GRAPHBASE_LIB_HDRS
    ${ESTD_HDRS}
    ${ALGO_HDRS}
    ${CONVERSIONS_HDRS}
    ${GRAPHSOURCE_HDRS}
    ${ORACLE_HDRS}
)

add_library(GraphbaseLib ${GRAPHBASE_LIB_SRCS} ${GRAPHBASE_LIB_HDRS})
target_link_libraries(GraphbaseLib ProtoLib)


# Binaries
file(GLOB ORACLE_CLIENT_SRCS bins/oracle/client/*.cpp)
add_executable(OracleClient ${ORACLE_CLIENT_SRCS})
target_link_libraries(OracleClient GraphbaseLib ProtoLib ${GRPC_LIBS})

file(GLOB ORACLE_SERVER_SRCS bins/oracle/server/*.cpp)
add_executable(OracleServer ${ORACLE_SERVER_SRCS})
target_link_libraries(OracleServer GraphbaseLib ProtoLib ${GRPC_LIBS})

# Tests
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tst)

