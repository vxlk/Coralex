#pragma once
#include "ITransaction.hpp"
#include "DBTypes.hpp"
#include <unordered_map>
#include "../parseXML.h"

namespace db {

// opened from the db cache, populated in the DBMS
// this data structure is used as a utility for naming
// and easily keeping track of which files in the db 
// are currently open
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
	
	std::unordered_map<DBType, DBObject> m_dbObjects;
	std::unordered_map<DBType, ParseXML> m_Files;
	std::vector<DBObject> m_OpenDBObjects;

	// Open the database cache
	// Populate the database objects
	DBMS();

public:

	static DBMS& Get() {
		static DBMS dbms;
		return dbms;
	}

	// Open a file within the database
	// Return: true if the file was successfully opened
	//		   An open file implies that transactions can be made to
	//		   this file - one transaction atomically at a time
	// Return: false if the file could not be opened
	//		   (more than likely already open)
	bool Open(DBType);
	
	// Attempt to close a file within the database
	// Return: true if the file was successfully closed
	//		   transactions can not be made to a file when
	//		   it is closed, it must be reopened to continue
	// Return: false if the file could not be closed
	//		   (implying an active transaction more than likely)
	bool Close(DBType);

	// Attempt to close all files within the database in one operation
	// Return: true if all files were successfully closed
	// Return: false if one or more files could not be closed
	//		   (note) use GetOpenFileList() to see which files are open
	bool Close();

	// Return all currently open files within the database
	const std::vector<DBObject>& GetOpenFiles();

	// An optimized version of GetOpenFiles() that does not perform a check
	// that it is up to date, use when cpu is a needed resource and accuracy is not
	const std::vector<DBObject>& GetOpenFilesNoCheck() const;
};
}
