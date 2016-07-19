#pragma once

#include <map>

#include "AbstractServer.h"
#include "PacketHandler.h"

class Client;

class Server : public AbstractServer
{
public:
	Server();

	virtual void Init(int port) override;
	virtual void Destroy() override;

	void Run();

private:
	virtual void OnAccept(FG::ConnectionPointer& conn) override;

	std::map<int, std::shared_ptr<Client>> clientList;
	std::unique_ptr<PacketHandler<Client>> handler;
};