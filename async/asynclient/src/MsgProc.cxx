#include "MsgProc.h"

void guide::HelloProc::process()
{
	_proc->onRsp(_rsp.message());
	delete this;
}

