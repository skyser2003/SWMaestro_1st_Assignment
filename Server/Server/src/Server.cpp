#include "stdafx.h"
#include "Server.h"

#include "FGServer.h"
#include "Client.h"

#include "PkEnumInfoHelper.h"

Server::Server()
{

}

void Server::Init(int port)
{
	AbstractServer::Init(port);

	handler.reset(new PacketHandler<Client>);
	handler->Init<GetIntVal(PKENUM::CSPacketEnum::CS_BEGIN), GetIntVal(PKENUM::CSPacketEnum::CS_END)>();
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

void Server::OnAccept(FG::ConnectionPointer& conn)
{
	auto client = std::shared_ptr<Client>(new Client);
	client->Init(conn);

	clientList[conn->GetID()] = client;
}