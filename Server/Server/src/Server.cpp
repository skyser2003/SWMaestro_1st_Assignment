#include "stdafx.h"
#include "Server.h"

#include "FGServer.h"
#include "Client.h"
#include "DBManager.h"
#include "NetworkClient.h"

#include "PkEnumInfoHelper.h"

Server::Server()
{

}

Server::~Server()
{

}

void Server::Init(int port)
{
	AbstractServer::Init(port);

	handler.reset(new PacketHandler<Client>);
	handler->Init<GetIntVal(PKENUM::CSPacketEnum::CS_BEGIN), GetIntVal(PKENUM::CSPacketEnum::CS_END)>();

	db.reset(new DBManager);
	db->Init("db");
}

void Server::Destroy()
{

}

void Server::Run()
{
	while (true)
	{
		server->Run();
	}
}

DBManager* Server::GetDB() const
{
	return db.get();
}

void Server::OnAccept(FG::ConnectionPointer& conn)
{
	// User
	auto client = std::shared_ptr<Client>(new Client);
	auto* netClient = new NetworkClient;

	netClient->Init(conn);
	netClient->SetPacketHandler([this, client = client.get()](int id, int length, char* data) -> bool
	{
		return handler->OnPacketReceive(client, id, length, data);
	});
	netClient->SetDisconnectHandler(std::bind(&Server::OnDisconnect, this, client));

	client->Init(this, netClient);

	clientList[conn->GetID()] = client;
}

void Server::OnDisconnect(std::shared_ptr<Client> client)
{
	for (auto pair : clientList)
	{
		if (pair.second == client)
		{
			clientList.erase(pair.first);
			return;
		}
	}
}