#include <iostream>
#include "HelloClient.h"

class HelloRspProcObserver : public guide::HelloRspProcI {
public:
	virtual void onRsp(std::string message) override
	{
		std::cout << "Received message: " << message << std::endl;
	}
};

int main(int argc, char* argv[])
{
	guide::HelloClient client(grpc::CreateChannel(
		"localhost:55555", grpc::InsecureChannelCredentials()));
	std::string user("John");
	HelloRspProcObserver ob;
	client.asyncSayHello(user, &ob);

	getchar();
	return 0;
}