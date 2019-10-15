mkdir build
cd build
export CC=/usr/bin/clang
export CXX=/usr/bin/clang++
cmake -D GRPC_CPP_PLUGIN="`which grpc_cpp_plugin`" -DCMAKE_BUILD_TYPE="Debug" ../src
