#pragma once
#include "parseXML.h"
#include <vector>

class State
{
		///state
		//		parent name  type
		std::map<std::string, std::string> strings;
		std::map<std::string, int>    ints;
		std::map<std::string, double> doubles;
		std::map<std::string, float>  floats;
		std::map<std::string, bool>   bools;

	public:

		void fill();

		bool operator==(const State& other)
		{
			bool isEqual = true; //assume true until proven otherwise
			if (this->strings != other.strings) isEqual = false;
			if (this->ints != other.ints) isEqual = false;
			if (this->doubles != other.doubles) isEqual = false;
			if (this->floats != other.floats) isEqual = false;
			if (this->bools != other.bools) isEqual = false;
		}
};

class StateManager
{
	State cache;
	
	State& getInput(); //the function that reads the xml..

	//temp
	std::map<std::string, std::string> _cache; //for now just use strings, maybe no reason to over engineer

public:

	bool checkForChange() { return this->cache == this->getInput(); }
	bool _checkForChange() 
	{
		
	}
};

