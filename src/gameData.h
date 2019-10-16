#pragma once
#include <string>
#include <map>
#include "vector2f.h"
#include "parseXML.h"

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

	Gamedata& operator=(const Gamedata&) = delete;

	bool operator==(const Gamedata&);
	Gamedata(const std::string& fn = "src/xmlSpec/game.xml");
private:
	ParseXML parser;
	const map<std::string, std::string> gameData;

	
};

inline bool Gamedata::operator==(const Gamedata& rhs)
{
	return this->gameData == rhs.gameData;
}