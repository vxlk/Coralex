#pragma once
#include <string>
#include "blob.hpp"

namespace lang {

/// An interpreter is a stateless entity responsible for translating commands
/// An Interpreter is responsible for: 
/// intaking a string
/// deciding whether the string is a valid command
/// acting on whether the string is a valid command
class Interpreter {

public:
	
	enum class LineInterpretation {
		IsFunction = 0,
		IsAssignment,
		IsComment
	};

	/// leave this default for now, might take an instance to the text editor
	Interpreter() = default;

	/// return whether it was a valid command
	/// if it was a valid command, the string will contain new data
	bool Interpret(std::string& command);

private:
	void ActOnString(std::string& commandModified, LineInterpretation);
	blob::Blob ExtractArgs(const std::string& commandUnmodified);
	std::string ExtractFunctionName(const std::string& commandUnmodified);

};

} // namespace lang