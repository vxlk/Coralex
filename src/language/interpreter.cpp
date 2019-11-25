#include "interpreter.hpp"
#include "basicFunctions.hpp"

namespace lang {

Blob Interpreter::ExtractArgs(const std::string &commandUnmodified) {
	int index = 0;
	std::vector<Blob> args;
	std::string blobName;
	unsigned long long argIndex = 0;
	while (commandUnmodified[index] != '(') 
		++index;
	++index; // skip parenthesis

	// might need to check for \r\n for windows platforms
	while (commandUnmodified[index] != ')') {
		while (commandUnmodified[index] != ',') {
			blobName += commandUnmodified[index];
		}
		++argIndex; // we added another arg
		args.emplace_back(blob::Get(blobName));

		//now we are done with the name, move on to the next
		blobName.clear();
	}
}

// currently unsafe
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

	// big todo here : ill want an xml with all function stuff eventually. to get this working im just
	// gonna hard code basic functions

	if (command == "add")
		//deal with args
		auto args = ExtractArgs(command); //args are now named arg1, arg2, etc
		
}

}