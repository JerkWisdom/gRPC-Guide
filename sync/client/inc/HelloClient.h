#ifndef __CLIENT_INC_CLIENT_H__
#define __CLIENT_INC_CLIENT_H__

#include <memory>
#include <string>
#include <grpc++/grpc++.h>
#include "sync.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using guide::HelloRequest;
using guide::HelloResponse;
using guide::HelloSvc;

namespace guide {
	class HelloClient
	{
	public:
		HelloClient(std::shared_ptr<Channel> channel)
			: _stub(HelloSvc::NewStub(channel)) { }
		~HelloClient() = default;

		std::string sayHello(const std::string name);

	private:
		std::unique_ptr<HelloSvc::Stub> _stub;
	};
}
#endif // __CLIENT_INC_CLIENT_H__