#pragma once

#include <map>

#include "AbstractServer.h"
#include "PacketHandler.h"

class Client;
class DBManager;

class Server : public AbstractServer
{
public:
	Server();
	~Server();

	virtual void Init(int port) override;
	virtual void Destroy() override;

	void Run();

private:
	virtual void OnAccept(FG::ConnectionPointer& conn) override;

	std::map<int, std::shared_ptr<Client>> clientList;
	std::unique_ptr<PacketHandler<Client>> handler;

	std::unique_ptr<DBManager> db;
};