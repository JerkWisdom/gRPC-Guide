#pragma once
#include <grpc++/grpc++.h>
#include "hello.grpc.pb.h"

namespace guide {
	class MsgProc {
	public:
		MsgProc(HelloSvc::AsyncService *service, grpc::ServerCompletionQueue *cq)
			: _service(service), _cq(cq), _status(CREATE)
		{
		}
		virtual void proceed() = 0;
	protected:
		HelloSvc::AsyncService       *_service;
		grpc::ServerCompletionQueue  *_cq;
		grpc::ServerContext           _ctx;

		enum { CREATE, PROCESS, FINISH } _status;
	};

	class HelloProc : public MsgProc {
	public:
		HelloProc(HelloSvc::AsyncService *service, grpc::ServerCompletionQueue *cq)
			: MsgProc(service, cq), _responder(&_ctx)
		{
			proceed();
		}
		virtual void proceed();
	private:
		HelloRequest  _req;
		HelloResponse _rsp;
		grpc::ServerAsyncResponseWriter<HelloResponse> _responder;
	};
}