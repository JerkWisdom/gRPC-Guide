#include "HelloClient.h"
#include <iostream>
#include "MsgProc.h"

guide::HelloClient::HelloClient(std::shared_ptr<Channel> channel)
	: _stub(HelloSvc::NewStub(channel))
	, _cq(new grpc::CompletionQueue())
	, _runnig(true)
	, _rpcTr(std::thread(&HelloClient::run, this))
{
}

guide::HelloClient::~HelloClient()
{
	_runnig = false;

	if (_cq) {
		_cq->Shutdown();
		delete _cq;
	}
	_rpcTr.join();
}

void guide::HelloClient::asyncSayHello(const std::string name, HelloRspProcI *proc)
{
	HelloProc *hp = new HelloProc(proc);
	HelloRequest req;
	req.set_name(name);

	std::cout << "Sent name: " << req.name() << std::endl;

	hp->_reader = _stub->AsyncsayHello(&hp->_ctx, req, _cq);
	hp->_reader->Finish(&hp->_rsp, &hp->_status, hp);
}

void guide::HelloClient::run()
{
	void *tag = NULL;
	bool ok = false;
	grpc::CompletionQueue::NextStatus got = grpc::CompletionQueue::NextStatus::TIMEOUT;
	MsgProc* proc = NULL;
	gpr_timespec deadline;
	deadline.clock_type = GPR_TIMESPAN;
	deadline.tv_sec = 0;
	deadline.tv_nsec = 10000000;
	while (true) {
		if (_cq) {
			got = _cq->AsyncNext<gpr_timespec>(&tag, &ok, deadline);
			if (grpc::CompletionQueue::NextStatus::GOT_EVENT == got && ok) {
				proc = reinterpret_cast<MsgProc*>(tag);
				if (proc) {
					proc->process();
				}
			}
		}
	}
}
