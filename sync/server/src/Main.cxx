#include <memory>
#include <iostream>
#include "HelloService.h"

void runServer()
{
	std::cout << "server run at 0.0.0.0:50051" << std::endl;

	std::string serverAddress("0.0.0.0:50051");
	guide::HelloService service;

	ServerBuilder builder;
	builder.AddListeningPort(serverAddress, grpc::InsecureServerCredentials());
	builder.RegisterService(&service);
	std::unique_ptr<Server> server(builder.BuildAndStart());
	server->Wait();
}

int main(int argc, char* argv[])
{
	runServer();

	return 0;
}