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

	DBManager* GetDB() const;

private:
	virtual void OnAccept(FG::ConnectionPointer& conn) override;
	void OnDisconnect(std::shared_ptr<Client> client);

	std::map<int, std::shared_ptr<Client>> clientList;
	std::unique_ptr<PacketHandler<Client>> handler;

	std::unique_ptr<DBManager> db;
};