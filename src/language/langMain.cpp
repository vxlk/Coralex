//this is used for testing the language independent of the game.
//have the coralex main call this function using lang::langMain()

#include "parser.hpp"
#include <fstream>

namespace lang {

	void langMain() {
		Parser p;

		//todo make this a file interface class, so you can have multiple files
		while (1) {
			std::string contents{ "" };
			std::ifstream f;
			f.open("C:/Users/small/Desktop/Coralex/Coralex/src/language/langTest.txt");

			//put into string
			f.seekg(0, std::ios::end);
			contents.reserve(f.tellg());
			f.seekg(0, std::ios::beg);

			contents.assign((std::istreambuf_iterator<char>(f)),
							 std::istreambuf_iterator<char>());
			//get the string of the file
			
			//run it thru the parser
			p.run(contents);
		}
	}
}