#pragma once
#include <string>
#include <grpc++/grpc++.h>
#include "hello.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using guide::HelloResponse;
using guide::HelloRequest;
using guide::HelloSvc;

namespace guide {
	class HelloService
	{
	public:
		HelloService();
		~HelloService();

		void run(const std::string &addr);
		void handleRPCs();

	private:
		HelloSvc::AsyncService                       _service;
		std::unique_ptr<grpc::ServerCompletionQueue> _cq;
		std::unique_ptr<grpc::Server>                _server;
	};
}