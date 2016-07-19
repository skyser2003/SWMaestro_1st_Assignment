#pragma once

#include <memory>

#include "FGConnection.h"

class Client
{
public:
	~Client();

	void Init(FG::ConnectionPointer conn);

	template <class Message>
	void OnPacketReceive(const Message& msg);

private:
	FG::ConnectionPointer conn = nullptr;
};