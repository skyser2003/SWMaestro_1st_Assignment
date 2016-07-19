#pragma once

#include "PksInfo.h"

template <class Message>
constexpr int GetPKSID()
{
	return PKSInfo<Message>::enumVal;
}