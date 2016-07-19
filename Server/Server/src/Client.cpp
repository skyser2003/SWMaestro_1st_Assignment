#include "stdafx.h"
#include "Client.h"

#include "PksInfo.h"
#include "Server.h"
#include "DBManager.h"
#include "PacketHeader.h"

using namespace PKS;

Client::~Client()
{
}

void Client::Init(Server* server, FG::ConnectionPointer conn)
{
	this->server = server;
	this->conn = conn;
	std::cout << "Connect success" << std::endl;
}

void Client::Send(int id, const google::protobuf::Message& msg)
{
	int msgSize = msg.ByteSize();
	int bufferSize = Packet::Header::Size + msgSize;

	Packet::Header header;
	header.packetID = id;
	header.length = msgSize;

	auto buffer = std::unique_ptr<char[]>(new char[bufferSize]);
	header.Serialize(buffer.get());

	msg.SerializeToArray(buffer.get() + Packet::Header::Size, msgSize);

	conn->Send(bufferSize, buffer.get());
}

template <>
void Client::OnPacketReceive(const CS_HIGH_SCORE& pks)
{
	auto* db = server->GetDB();
	db->SetHighScore(pks.name(), pks.score());

	auto dbScoreList = db->GetScoreList();
	
	SC_HIGH_SCORE_LIST outPks;

	auto* nameList = outPks.mutable_name();
	auto* scoreList = outPks.mutable_score();

	for (auto& score : dbScoreList)
	{
		*nameList->Add() = score.name;
		*scoreList->Add() = score.score;
	}

	Send(outPks);
}