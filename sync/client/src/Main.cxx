#include "HelloClient.h"

void runClient()
{
	guide::HelloClient client(grpc::CreateChannel(
		"localhost:50051", grpc::InsecureChannelCredentials()));
	std::string user("John");
	std::string rsp = client.sayHello(user);
	std::cout << "Hello Client Received: " << rsp << std::endl;

}

int main(int argc, char* argv[])
{
	runClient();

	getchar();
	return 0;
}