#include "stdafx.h"
#include "PacketHeader.h"

namespace Packet
{
	Header::Header()
	{
		Init();
	}

	void Header::Init()
	{
		packetID = -1;
		length = -1;
	}

	Header::Buffer Header::Serialize()
	{
		Buffer buffer;
		buffer.data = new char[Size];

		memcpy(buffer.data, &packetID, sizeof(packetID));
		memcpy(buffer.data + sizeof(packetID), &length, sizeof(length));

		return buffer;
	}

	void Header::Serialize(void* buffer)
	{
		memcpy(buffer, &packetID, sizeof(packetID));
		memcpy(static_cast<char*>(buffer) + sizeof(packetID), &length, sizeof(length));
	}

	void Header::Deserialize(Buffer buffer)
	{
		Deserialize(buffer.data);
	}

	void Header::Deserialize(char* data)
	{
		memcpy(&packetID, data, sizeof(packetID));
		memcpy(&length, data + sizeof(packetID), sizeof(length));
	}
}