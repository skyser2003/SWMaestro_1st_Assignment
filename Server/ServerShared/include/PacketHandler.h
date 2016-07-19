#pragma once

#include <map>
#include <functional>

#include "google/protobuf/message.h"

#include "PkEnumInfo.h"
#include "PksInfo.h"

template <class T>
class PacketHandler
{
public:
	using parserFunc = std::function<bool(T*, int, char*)>;

	template <int BEGIN, int INT_END>
	void Init()
	{
		Register<INT<BEGIN + 1>>(INT<INT_END>(), nullptr);
	}

	bool OnPacketReceive(T* caller, int id, int size, char* data)
	{
		if (parserList.count(id) == 0)
		{
			return false;
		}
		else
		{
			return parserList[id](caller, size, data);
		}
	}

private:
	template <int VAL>
	struct INT
	{
		enum
		{
			val = VAL
		};
	};

	template <class INT1, class INT_END>
	void Register(INT_END END, typename PKENUMInfo<INT1::val>::PKS* pks)
	{
		using Message = typename std::remove_reference<decltype(*pks)>::type;

		parserList.emplace(INT1::val, std::bind(&PacketHandler::OnParse<Message>, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

		Register<INT<INT1::val + 1>>(END, nullptr);
	}

	template <class INT1, class INT_END>
	void Register(INT_END END, ...)
	{
		Register<INT<INT1::val + 1>>(END, nullptr);
	}

	template <class INT_END>
	void Register(INT_END, INT_END*)
	{
		// End
	}

	template <class Message>
	bool OnParse(T* caller, int size, char* data)
	{
		Message msg;
		bool succeed = msg.ParseFromArray(data, size);

		if (succeed == false)
		{
			return false;
		}
		else
		{
			caller->OnPacketReceive(msg);
			return true;
		}
	}

	std::map<int, parserFunc> parserList;
};