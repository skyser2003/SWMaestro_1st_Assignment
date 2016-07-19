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

bool DBManager::SetFamilyName(int uid, const std::string& familyName)
{
	if (db == nullptr)
	{
		return false;
	}

	std::string query = (boost::format("UPDATE ACCOUNT SET family_name = '%s' WHERE uid = %s") % familyName % uid).str();

	return db->Query(query);
}

int DBManager::GetAccountUid(const std::string& id)
{
	if (db == nullptr)
	{
		return -1;
	}

	int uid = -1;

	std::string query = (boost::format("SELECT uid FROM ACCOUNT WHERE id = '%s'") % id).str();

	db->Query(query, [&uid](int numCoumn, char** fieldList, char** columnNameList)
	{
		uid = std::stoi(fieldList[0]);
	});

	return uid;
}

bool DBManager::SetFieldState(int uid, int fieldID, int characterState)
{
	if (db == nullptr)
	{
		return false;
	}

	std::string query = (boost::format("INSERT OR REPLACE INTO USER_FIELD_INFO (uid, field_id, character_state) VALUES (%d, %d, %d)") % uid % fieldID % characterState).str();
	return db->Query(query);
}