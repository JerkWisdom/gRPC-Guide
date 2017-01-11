#include "HelloClient.h"

std::string guide::HelloClient::sayHello(std::string name)
{
	HelloRequest req;
	req.set_name(name);

	HelloResponse rsp;
	ClientContext ctx;
	
	Status status = _stub->sayHello(&ctx, req, &rsp);
	if (status.ok()) {
		std::cout << "Sent name: " << req.name() << std::endl;
		std::cout << "Received message: " << rsp.message() << std::endl;
		return rsp.message();
	} else {
		return "RPC Failed.";
	}
}