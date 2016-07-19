#pragma once

#include <memory>
#include <string>

class DB;

struct Score
{
	std::string name;
	int score;
};

class DBManager
{
public:
	DBManager();
	~DBManager();

	void Init(const std::string& dbName);

	bool SetHighScore(const std::string& name, int score);
	std::vector<Score> GetScoreList();

private:
	std::unique_ptr<DB> db;
};