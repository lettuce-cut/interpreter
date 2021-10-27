#include "Lexer.h"
#include "DatalogProgram.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

int main (int argc, char** argv) {
    std::ifstream ifs;
    std::string input;
    std::string fileName = argv[1];
    std::stringstream s;

    auto* lexer = new Lexer();

    ifs.open(fileName);
    if (!ifs.is_open()) {
        std::cout << "File " << fileName << " could not open." << std::endl;
    }


    s << ifs.rdbuf();
    input = s.str();

    ifs.close();

    Lexer myLexer = Lexer();
//    myLexer.toString(Lexer().Run(input));

    try {
        DatalogProgram myParser = DatalogProgram();
        myParser.parseRun(myLexer.Run(input));
        std::cout << "Success!" << std::endl;
        myParser.outputString();
    }
    catch (std::string error) {
        std::cout << "Failure!" << std::endl;
        std::cout << "  " << error << std::endl;
    }
//    std::cout << "Hello World" << std::endl;

    delete lexer;

    return 0;
}