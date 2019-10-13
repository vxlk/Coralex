#pragma once
#include "src/parseXML.h"
#include <vector>

class StateManager
{
	///state
	//		parent name  type
	std::map<std::string, std::string> strings;
	std::map<std::string, int>    ints;
	std::map<std::string, double> doubles;
	std::map<std::string, float>  floats;
	std::map<std::string, bool>   bools;


public:

};

