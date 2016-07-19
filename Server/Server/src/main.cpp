#include "stdafx.h"
#include "server.h"

using namespace std;

int main()
{
	Server server;
	server.Init(3999);

	server.Run();

	return 0;
}