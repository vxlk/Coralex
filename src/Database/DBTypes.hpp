#pragma once

#include <string>

namespace db {

	// The key used to open a document within the database
	enum class DBType {
		eDBCache
	};

	// Turn a database type into the string
	inline std::string DBTypeToString(DBType type) {
		switch (type)
		{
			case DBType::eDBCache:
				return "DBCache";
			default:
				break;
		}
	}

	// Turn a string into a database type
	inline DBType StringToDBType(const std::string& type) {
		if (type == "DBCache")
			return DBType::eDBCache;
	}
}
