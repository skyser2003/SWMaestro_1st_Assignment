#include "stdafx.h"
#include "Client.h"

#include "PksInfo.h"
#include "Server.h"
#include "DBManager.h"
#include "PacketHeader.h"
#include "NetworkClient.h"

using namespace PKS;

Client::~Client()
{
}

void Client::Init(Server* server, NetworkClient* netClient)
{
	this->server = server;
	this->netClient.reset(netClient);
	std::cout << "Connect success" << std::endl;
}

void Client::Send(int id, const google::protobuf::Message& msg)
{
	netClient->Send(id, msg);
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