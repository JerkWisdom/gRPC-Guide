#include "HelloClient.h"

std::string guide::HelloClient::sayHello(std::string user)
{
	HelloRequest req;
	req.set_name(user);

	HelloResponse rsp;
	ClientContext ctx;
	
	Status status = _stub->sayHello(&ctx, req, &rsp);
	if (status.ok()) {
		return rsp.message();
	} else {
		return "RPC Failed.";
	}
}
