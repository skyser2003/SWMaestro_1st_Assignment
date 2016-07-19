#include "stdafx.h"
#include "AbstractServer.h"

#include "NetworkClient.h"
#include "FGServer.h"
#include "PacketHandler.h"

AbstractServer::AbstractServer() : server(new FG::Server)
{

}

AbstractServer::~AbstractServer()
{

}

void AbstractServer::Init(int port)
{
	server->Bind(port);
	server->Listen();
	server->SetAcceptHandler(std::bind(&AbstractServer::OnAccept, this, std::placeholders::_1));
}