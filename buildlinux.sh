rPath=`pwd`

$rPath/thirdparty/gRPC/bins/opt/protobuf/protoc -I $rPath/protos/sync --grpc_out=$rPath/sync/client/src --grpc_out=$rPath/sync/server/src --cpp_out=$rPath/sync/client/src --cpp_out=$rPath/sync/server/src --plugin=protoc-gen-grpc=$rPath/thirdparty/gRPC/bins/opt/grpc_cpp_plugin $rPath/protos/sync/sync.proto

mkdir $rPath/build/
mkdir $rPath/build/linux
cd $rPath/build/linux
cmake ../.. -G"Unix Makefiles"
make