#include "parser.hpp"
#include <sstream>

namespace lang {
	void Parser::run(const std::string& contents) {
		std::istringstream stream(contents); // make it readable from getline
		for (std::string line; std::getline(stream, line);)
			this->interpreter.Interpret(line);
	}
}