#include "stdafx.h"
#include "DBManager.h"

#include "DB.h"

DBManager::DBManager()
{

}

DBManager::~DBManager()
{
	if (db != nullptr)
	{
		db->Close();
		db.reset();
	}
}

void DBManager::Init(const std::string& dbName)
{
	db.reset(new DB);
	db->Init();
	db->Connect(dbName);
}

/*
bool DBManager::Join(const std::string& id, const std::string& pw)
{
	if (db == nullptr)
	{
		return false;
	}

	std::string query = "INSERT INTO ACCOUNT (id, pw) VALUES ('" + id + "', '" + pw + "')";

	return db->Query(query);
}

bool DBManager::Login(const std::string& id, const std::string& pw)
{
	if (db == nullptr)
	{
		return false;
	}

	std::string query = "SELECT count(*) FROM ACCOUNT WHERE id = '" + id + "' AND pw = '" + pw + "'";

	bool ret = false;

	db->Query(query, [&ret](int numColumn, char** fieldList, char** columnNameList)
	{
		int count = std::stoi(fieldList[0]);
		ret = (count == 1);
	});

	return ret;
}
*/

bool DBManager::SetHighScore(const std::string& name, int score)
{
	if (db == nullptr)
	{
		return false;
	}

	std::string query = (boost::format("INSERT OR REPLACE INTO HIGH_SCORE (name, score) VALUES (%d, %d, %d)") % name % score).str();
	return db->Query(query);
}

std::vector<Score> DBManager::GetScoreList()
{
	std::vector<Score> ret;

	std::string query = (boost::format("SELECT * FROM HIGH_SCORE ORDER BY score").str());
	db->Query(query, [&ret](int numColumn, char** fieldList, char** columnNameList)
	{
		Score score;

		for (int i = 0; i < numColumn; ++i)
		{
			char* columnName = columnNameList[i];
			char* field = fieldList[i];

			if (strcmp(columnName, "score") == 0)
			{
				score.score = atoi(field);
			}
			else if (strcmp(columnName, "name") == 0)
			{
				score.name = field;
			}
		}

		ret.push_back(score);
	});

	return ret;
}