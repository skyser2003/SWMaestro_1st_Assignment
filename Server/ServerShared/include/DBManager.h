#pragma once

#include <memory>
#include <string>

class DB;

class DBManager
{
public:
	DBManager();
	~DBManager();

	void Init(const std::string& dbName);

	// Account
	bool Join(const std::string& id, const std::string& pw);
	bool Login(const std::string& id, const std::string& pw);
	bool SetFamilyName(int uid, const std::string& familyName);

	int GetAccountUid(const std::string& id);

	// Field
	bool SetFieldState(int uid, int fieldID, int characterState);

private:
	std::unique_ptr<DB> db;
};