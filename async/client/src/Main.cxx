#include "HelloClient.h"

int main(int argc, char* argv[])
{
	guide::HelloClient client(grpc::CreateChannel(
		"localhost:55555", grpc::InsecureChannelCredentials()));
	std::string user("John");
	std::string rsp = client.sayHello(user);

	getchar();
	return 0;
}