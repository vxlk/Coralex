#pragma once
#include "ITransaction.hpp"
#include "DBTypes.hpp"

namespace db {

// opened from the db cache, populated in the DBMS
struct DBObject {
	DBObject(const std::string& filePath, DBType alias)
		: m_FilePath(filePath), m_Name(alias)
	{}
	DBType m_Name;
	std::string m_FilePath;
	bool isOpen = false;
};

// This object represents the database management system
// it manages the underlying database (collection of xml files)
// todo: description - this is an important object
class DBMS {
	
	std::vector<DBObject> m_dbObjects;

	// Open the database cache
	// Populate the database objects
	DBMS();

public:

	static DBMS& Get() {
		static DBMS dbms;
		return dbms;
	}

	bool Open(DBType);
};
}
