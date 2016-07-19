#include "stdafx.h"
#include "NetworkClient.h"

#include "AbstractServer.h"
#include "PacketHandler.h"

#include <iostream>
using namespace std;
using namespace std::placeholders;

void NetworkClient::Init(FG::ConnectionPointer& conn)
{
	this->conn = conn;

	conn->SetReceiveHandler(std::bind(&NetworkClient::OnReceive, this, _1, _2));
	conn->SetDisconnectHandler(std::bind(&NetworkClient::OnDisconnect, this));
}

void NetworkClient::ParsePacket()
{
	while (true)
	{
		// Parse header
		if (header.packetID == -1 && Packet::Header::Size <= buffer.size())
		{
			header.Deserialize(buffer.data());
			buffer.erase(buffer.begin(), buffer.begin() + Packet::Header::Size);
		}
		// Parse body
		else if (header.packetID != -1 && header.length <= buffer.size())
		{
			if (packetHandler != nullptr)
			{

				bool succeed = packetHandler(header.packetID, header.length, buffer.data());

				if (succeed == false)
				{
					// TODO : error
				}
			}

			buffer.erase(buffer.begin(), buffer.begin() + header.length);
			header.Init();
		}
		// Wait 'till data is ready
		else
		{
			break;
		}
	}
}

void NetworkClient::OnReceive(int size, char* data)
{
	buffer.insert(buffer.end(), data, data + size);

	ParsePacket();
}

void NetworkClient::SetPacketHandler(PacketHandler packetHandler)
{
	this->packetHandler = packetHandler;
}

void NetworkClient::SetDisconnectHandler(DisconnectHandler disconnectHandler)
{
	this->disconnectHandler = disconnectHandler;
}

void NetworkClient::Send(int packetID, const google::protobuf::Message& msg)
{
	int msgSize = msg.ByteSize();
	int bufferSize = Packet::Header::Size + msgSize;

	Packet::Header header;
	header.packetID = packetID;
	header.length = msgSize;

	auto buffer = std::unique_ptr<char[]>(new char[bufferSize]);
	header.Serialize(buffer.get());

	msg.SerializeToArray(buffer.get() + Packet::Header::Size, msgSize);

	conn->Send(bufferSize, buffer.get());
}

void NetworkClient::OnDisconnect()
{
	cout << "Disconnected : " << conn->GetID() << endl;

	if (disconnectHandler != nullptr)
	{
		disconnectHandler();
	}
}