mkdir cmake_dir
cd cmake_dir
cmake -D GRPC_CPP_PLUGIN="`which grpc_cpp_plugin`" ../src
