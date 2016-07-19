#pragma once

#include <memory>

#include "FGConnection.h"

namespace FG
{
	class Server;
}

class AbstractServer
{
public:
	AbstractServer();
	virtual ~AbstractServer();

	virtual void Init(int port) = 0;
	virtual void Destroy() = 0;

protected:
	virtual void OnAccept(FG::ConnectionPointer& conn) = 0;

	std::unique_ptr<FG::Server> server;
};