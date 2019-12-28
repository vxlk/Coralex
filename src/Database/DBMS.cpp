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
				// cant open an already open file
				return false;
			else {
				// open the file
				m_Files.insert({ objectName, ParseXML(object.second.m_FilePath) });
				// the xml is read, it is now open
				object.second.isOpen = true;
				// add to open file list
				m_OpenDBObjects.emplace_back(object.second);
			}
	return true;
}

bool DBMS::Close(DBType typeName) {
	bool wasSuccess = false;
	for (const auto& object : m_OpenDBObjects) {
		if (object.m_Name == typeName) {
			m_OpenDBObjects.erase(std::remove(m_OpenDBObjects.begin(), m_OpenDBObjects.end(), object), 
									m_OpenDBObjects.end());
			wasSuccess = true;
		}
	}
	return wasSuccess;
}

bool DBMS::Close() {
	if (m_dbObjects.empty()) return false;
	m_dbObjects.clear();
	return true;
}
} // namespace db