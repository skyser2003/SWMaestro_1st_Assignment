#include "stdafx.h"
#include "Client.h"

#include "PksInfo.h"
using namespace PKS;

Client::~Client()
{
}

void Client::Init(FG::ConnectionPointer conn)
{
	this->conn = conn;
	std::cout << "Connect success" << std::endl;
}

template <>
void Client::OnPacketReceive(const CS_HIGH_SCORE& pks)
{

}