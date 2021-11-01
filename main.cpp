#include "Lexer.h"
#include "DatalogProgram.h"
#include "Interpreter.h"
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

    std::vector<Predicate> schemesMain;
    std::vector<Predicate> factsMain;
    std::vector<Predicate> queriesMain;
    std::vector<Rule> rulesMain;

    try {
        DatalogProgram myParser = DatalogProgram();
        myParser.parseRun(myLexer.Run(input));
        std::cout << "Success!" << std::endl;
        myParser.outputString();
        schemesMain = myParser.getSchemes();
        factsMain = myParser.getFacts();
        queriesMain = myParser.getQueries();
        rulesMain = myParser.getRules();
    }
    catch (std::string error) {
        std::cout << "Failure!" << std::endl;
        std::cout << "  " << error << std::endl;
    }

    Interpreter myInterpreter = Interpreter(schemesMain, factsMain, queriesMain, rulesMain);
    std::cout << std::endl << "IN INTERPRETER" << std::endl << std::endl;
//    myInterpreter.InterpreterRun();
    myInterpreter.makeRelation();

//    std::cout << "Hello World" << std::endl;

    delete lexer;

    return 0;
}