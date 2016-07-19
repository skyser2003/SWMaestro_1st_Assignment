#pragma once

#include <memory>

#include "FGConnection.h"
#include "PksInfoHelper.h"

class Server;
class NetworkClient;

class Client
{
public:
	~Client();

	void Init(Server* server, NetworkClient* netClient);

	template <class Message>
	void Send(const Message& msg)
	{
		Send(GetPKSID<Message>(), msg);
	}

	void Send(int id, const google::protobuf::Message& msg);

	template <class Message>
	void OnPacketReceive(const Message& msg);

private:
	Server* server;
	std::unique_ptr<NetworkClient> netClient;
};