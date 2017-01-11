#include "HelloService.h"
#include <iostream>
#include "MsgProc.h"

guide::HelloService::HelloService()
{

}

guide::HelloService::~HelloService()
{
	_server->Shutdown();
	_cq->Shutdown();
}

void guide::HelloService::run(const std::string &addr)
{
	grpc::ServerBuilder builder;
	builder.AddListeningPort(addr, grpc::InsecureServerCredentials());
	builder.RegisterService(&_service);
	_cq = builder.AddCompletionQueue();
	_server = builder.BuildAndStart();

	std::cout << "Running async server from: " << addr << std::endl;

	handleRPCs();
}

void guide::HelloService::handleRPCs()
{
	new HelloProc(&_service, _cq.get());
	void *tag;
	bool ok;
	while (true){
		_cq->Next(&tag, &ok);
		GPR_ASSERT(ok);
		static_cast<HelloProc*>(tag)->proceed();
	}
}
