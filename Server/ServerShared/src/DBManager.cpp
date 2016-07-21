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

bool DBManager::SetHighScore(const std::string& name, int score)
{
	if (db == nullptr)
	{
		return false;
	}

	std::string query = (boost::format("INSERT OR REPLACE INTO HIGH_SCORE (name, score) VALUES ('%s', %d)") % name % score).str();
	return db->Query(query);
}

std::vector<Score> DBManager::GetScoreList()
{
	std::vector<Score> ret;

	std::string query = (boost::format("SELECT * FROM HIGH_SCORE ORDER BY score DESC").str());
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