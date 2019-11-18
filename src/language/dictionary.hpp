#pragma once

#include <unordered_map>
#include "blob.hpp"
#include "../parseXML.h"

// the dictionary holds a "list" of everything your program may reference
// if you make a blob named hello -> hello is added to the dictionary 
// meaning the interpreter may look up the name hello when it is referenced
// and be assured it exists within the program

// this is persistently stored in an xml
// but is loaded into memory on run-time for fast lookup speed

namespace lang {

class Dictionary {

	std::unordered_map<std::string, Blob> hashMap;
	ParseXML xml;

	void Write();
	void Read();

public:

	// open the hardcoded xml file name -> Read contents
	Dictionary();
	virtual ~Dictionary() = default;

	bool Add(std::string name, Blob data);
	bool Remove(std::string name);
};
} //namespace lang
