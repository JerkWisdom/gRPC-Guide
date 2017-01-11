#include "HelloService.h"

int main(int argc, char* argv[])
{
	guide::HelloService service;
	service.run("0.0.0.0:55555");

	return 0;
}