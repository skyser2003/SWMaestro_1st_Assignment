#include "stdafx.h"
#include "DB.h"

using namespace boost::filesystem;

DB::~DB()
{
	Close();
}

void DB::Init()
{
	curDir = current_path().string();
}

bool DB::Connect(const std::string& dbName)
{
	std::string filename = curDir + "/" + dbName + ".sqlite3";
	path path = filename;
	bool initDB = exists(path) == false;

	int rc = sqlite3_open(filename.c_str(), &sqlite);

	if (rc == SQLITE_OK)
	{
		if (initDB == true)
		{
			std::ifstream scheme;
			scheme.open("db_init_query.txt");

			std::string query;

			while (scheme)
			{
				std::string line;
				std::getline(scheme, line);

				query += line;
			}

			Query(query);
		}
	}
	else
	{
		std::cout << "DB::Connect error" << std::endl;
	}

	return rc == 0;
}

void DB::Close()
{
	if (sqlite == nullptr)
	{
		return;
	}

	int rc = sqlite3_close(sqlite);
	if (rc != SQLITE_OK)
	{
		std::cout << "DB::Close error" << std::endl;
	}
}

bool DB::Query(const std::string& query)
{
	return Query(query, nullptr);
}

bool DB::Query(const std::string& query, QueryCallbackType resultCallback)
{
	if (sqlite == nullptr)
	{
		return false;
	}

	char* errMsg;

	int rc = sqlite3_exec(sqlite, query.c_str(), &QueryCallback, &resultCallback, &errMsg);

	if (rc != SQLITE_OK)
	{
		std::cout << "SQLite query error : " << errMsg << std::endl;
	}

	return rc == SQLITE_OK;
}

int QueryCallback(void* data, int numColumn, char** fieldList, char** columnNameList)
{
	DB::QueryCallbackType* resultCallback = static_cast<DB::QueryCallbackType*>(data);

	(*resultCallback)(numColumn, fieldList, columnNameList);
	return 0;
}