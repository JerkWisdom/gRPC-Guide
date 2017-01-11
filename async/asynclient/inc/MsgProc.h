#pragma once
#include <memory>
#include <grpc++/grpc++.h>
#include "hello.grpc.pb.h"
#include "HelloClient.h"

using grpc::ClientAsyncResponseReader;
using guide::HelloRequest;
using guide::HelloResponse;

namespace guide {
	class MsgProc {
	public:
		virtual void process() = 0;

	protected:
		grpc::ClientContext _ctx;
		grpc::Status        _status;
	};

	class HelloProc : public MsgProc {
	public:
		HelloProc(HelloRspProcI *proc)
			: _proc(proc)
		{

		}
		virtual void process() override;

	private:
		friend class HelloClient;
		HelloRspProcI *_proc;
		HelloResponse  _rsp;
		std::unique_ptr<ClientAsyncResponseReader<HelloResponse>> _reader;
	};
}
