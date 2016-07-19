#pragma once

#include <vector>
#include <memory>
#include <functional>

#include "FGNetworkSharedHelper.h"
#include "PacketHeader.h"
#include "PksInfoHelper.h"

class AbstractServer;

class NetworkClient
{
public:
	using PacketHandler = std::function<bool(int, int, char*)>;
	using DisconnectHandler = std::function<void(void)>;

	void Init(FG::ConnectionPointer& conn);
	void ParsePacket();

	void OnReceive(int size, char* data);

	void SetPacketHandler(PacketHandler packetHandler);
	void SetDisconnectHandler(DisconnectHandler disconnectHandler);

	template <class Message>
	void Send(const Message& msg)
	{
		Send(GetPKSID<Message>(), msg);
	}

	void Send(int packetID, const google::protobuf::Message& msg);

private:
	void OnDisconnect();

	FG::ConnectionPointer conn;

	Packet::Header header;
	std::vector<char> buffer;

	PacketHandler packetHandler;
	DisconnectHandler disconnectHandler;
};