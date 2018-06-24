mkdir build
cd build
cmake -D GRPC_CPP_PLUGIN="`which grpc_cpp_plugin`" ../src
