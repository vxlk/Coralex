#pragma once
#include <string>
#include <map>
#include "vector2f.h"
#include "parseXML.h"
#include <vector>
#include "xml_info.h"

class Gamedata {
public:
	static Gamedata& getInstance();

	~Gamedata();
	void displayData() const;

	bool getXmlBool(const std::string&) const;
	const std::string& getXmlStr(const std::string&) const;
	float getXmlFloat(const std::string&) const;
	int getXmlInt(const std::string&) const;
	float getRandInRange(int min, int max) const;
	float getRandFloat(float min, float max) const;
	bool  checkTag(const std::string&) const;

	void checkForChange();
	void dealWithChange(Gamedata &snapshot);
	void Diff(Gamedata &new_data);

	map <std::string, std::string> data() { return gameData; }

	Gamedata& operator=(const Gamedata&) = delete;

	bool operator==(const Gamedata&);
	Gamedata(const std::string& fn = xmlMain);
private:
	ParseXML parser;
	const map<std::string, std::string> gameData;
	std::vector<std::pair<std::string, std::string>> diff;
};

inline bool Gamedata::operator==(const Gamedata& rhs)
{
	return this->gameData.size() == rhs.gameData.size(); //flag a change if anything happens to the file
}