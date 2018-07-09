cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB TEST_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/graph/algo/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/graph/graph/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/query/*.cpp
)
add_executable(TestAll ${TEST_SRCS} ${CMAKE_CURRENT_SOURCE_DIR}/graph/test_all.cpp)
target_link_libraries(TestAll GraphbaseLib)
