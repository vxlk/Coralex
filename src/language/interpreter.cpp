#include "interpreter.hpp"
#include "basicFunctions.hpp"


namespace lang {

blob::Blob Interpreter::ExtractArgs(const std::string &commandUnmodified) {
	int index = 0;
	std::vector<blob::Blob> args;
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

	//stub for now
	return {};
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
	
	// a line from the file is passed to this function
	// its job is to look at it and deduce whether it is
	// assignment, a function, or a comment and act accordingly
	return true;
}

void Interpreter::ActOnString(std::string& command, Interpreter::LineInterpretation) {

}

} // namespace lang