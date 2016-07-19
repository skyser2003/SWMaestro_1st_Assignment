#pragma once

#include <string>
#include <functional>

struct sqlite3;

class DB
{
public:
	~DB();

	using QueryCallbackType = std::function<void(int numColumn, char** fieldList, char** columnNameList)>;

	void Init();

	bool Connect(const std::string& dbName);
	void Close();

	bool Query(const std::string& query);
	bool Query(const std::string& query, QueryCallbackType resultCallback);

private:
	std::string curDir;

	sqlite3* sqlite;
};

int QueryCallback(void* data, int numColumn, char** fieldList, char** columnNameList);