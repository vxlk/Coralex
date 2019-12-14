#pragma once

#include <string>
#include "interpreter.hpp"

namespace lang {
/// this class takes in the contents of the file, if the file has changed
/// it looks at the file and reads the changes.
/// if the changes provide a valid token or set of tokens, it sends the 
/// commands to the interpreter where they are further broken down and
/// read as grammars.
class Parser {

	std::string contents;
	Interpreter interpreter;

public:

	void run(const std::string& fileContents);
};
}//namespace lang