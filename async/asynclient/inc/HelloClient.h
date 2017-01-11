#pragma once
#include <memory>
#include <string>
#include <thread>
#include <stdint.h>
#include <grpc++/grpc++.h>
#include "hello.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using guide::HelloRequest;
using guide::HelloResponse;
using guide::HelloSvc;

namespace guide {
	class HelloRspProcI {
	public:
		virtual void onRsp(std::string message) = 0;
	};

	class HelloClient
	{
	public:
		explicit HelloClient(std::shared_ptr<Channel> channel);
		~HelloClient();

		void asyncSayHello(const std::string name, HelloRspProcI *proc);
		
		void run();

		HelloClient(const HelloClient&) = default;
		HelloClient& operator=(const HelloClient&) = default;

	private:
		std::unique_ptr<HelloSvc::Stub> _stub;
		grpc::CompletionQueue          *_cq;
		std::thread                     _rpcTr;
		bool                            _runnig;
	};
}