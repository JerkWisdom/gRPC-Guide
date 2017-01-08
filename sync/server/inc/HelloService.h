#ifndef __SERVER_INC_CLIENT_H__
#define __SERVER_INC_CLIENT_H__

#include <string>
#include <grpc++/grpc++.h>
#include "sync.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using guide::HelloResponse;
using guide::HelloRequest;
using guide::HelloSvc;

namespace guide{
	class HelloService : public HelloSvc::Service
	{
	public:
		HelloService() = default;
		~HelloService() = default;

		virtual Status sayHello(ServerContext* context, const HelloRequest* req, HelloResponse* rsp) override;
	};
}

#endif // __SERVER_INC_CLIENT_H__