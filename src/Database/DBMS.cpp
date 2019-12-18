#include "DBMS.hpp"
#include <algorithm>

namespace db {

const std::vector<DBObject>& DBMS::GetOpenFiles() {
	// always make sure the list is up to date
	for (const auto& file : m_dbObjects) {
		if (file.second.isOpen) {
			if (std::find(m_OpenDBObjects.begin(), m_OpenDBObjects.end(), file.second) == m_OpenDBObjects.end())
				m_OpenDBObjects.emplace_back(file.second);
		}
	}
	return m_OpenDBObjects;
}

const std::vector<DBObject>& DBMS::GetOpenFilesNoCheck() const {
	return m_OpenDBObjects;
}

bool DBMS::Open(DBType objectName) {
	for (auto& object : m_dbObjects)
		if (object.first == objectName)
			if (object.second.isOpen)
				return false;
			else {
				// open the file
				m_Files.insert({objectName, ParseXML(object.second.m_FilePath)});
				object.second.isOpen = true;
			}
}
} // namespace db