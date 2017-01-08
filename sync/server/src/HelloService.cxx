#include "HelloService.h"

Status guide::HelloService::sayHello(ServerContext* context, const HelloRequest* req, HelloResponse* rsp)
{
	std::cout << "Received from client: " << req->name() << std::endl;
	std::string response = "hello, ";
	rsp->set_message(response + req->name());
	return Status::OK;
}