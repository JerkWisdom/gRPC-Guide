#include "MsgProc.h"
#include <iostream>

void guide::HelloProc::proceed()
{
	if (CREATE == _status) {
		_status = PROCESS;
		_service->RequestsayHello(&_ctx, &_req, &_responder, _cq, _cq, this);
	} else if (PROCESS == _status) {
		new HelloProc(_service, _cq);

		std::string response = "hello, " + _req.name();
		_rsp.set_message(response.c_str());
		_status = FINISH;
		_responder.Finish(_rsp, grpc::Status::OK, this);

		std::cout << "Received name: " << _req.name() << std::endl;
		std::cout << "Replied message: " << response << std::endl;
	} else {
		GPR_ASSERT(FINISH == _status);
		delete this;
	}
}

