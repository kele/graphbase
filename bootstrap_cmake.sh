mkdir build
cd build
cmake -D GRPC_CPP_PLUGIN="`which grpc_cpp_plugin`" -DCMAKE_BUILD_TYPE="Debug" ../src
