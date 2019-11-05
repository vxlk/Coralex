#include "interpreter.hpp"
#include "basicFunctions.hpp"

namespace lang {

Blob Interpreter::ExtractArgs(const std::string &commandUnmodified) {
	int index = 0;
	while (commandUnmodified[index] != '(') ++index;
	++index; // skip parenthesis

	// might need to check for \r\n for windows platforms
	while(commandUnmodified[index] != '\n')
}

std::string Interpreter::ExtractFunctionName(const std::string& commandUnmodified) {
	//from beginning of line to (
	std::string funcName = "";
	int index = 0;
	while (commandUnmodified[index] != '(') {
		funcName += commandUnmodified[index];
		++index;
	}
	return funcName;
}

/// public functions
bool Interpreter::Interpret(std::string &command) {
	//sees the command add
	//check against function dictionary
	//is it a match?
	//execute
	if (command == "add")
		//deal with args
		auto args = ExtractArgs(command); //args are now named arg1, arg2, etc
		
}

}