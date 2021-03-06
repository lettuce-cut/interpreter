#include "Lexer.h"
#include "DatalogProgram.h"
#include "Interpreter.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "Graph.h"
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

    DatalogProgram myParser = DatalogProgram();

    try {
        myParser.parseRun(myLexer.Run(input));
//        std::cout << "Success!" << std::endl;
//        myParser.outputString();

    }
    catch (std::string error) {
        std::cout << "Failure!" << std::endl;
        std::cout << "  " << error << std::endl;
    }

//    Interpreter myInterpreter(myParser);
//    myInterpreter.makeRelation(); //evaluates schemes and facts

    Graph myGraph(myParser);
    myGraph.makeRelation();

    myGraph.forwardDepend();
    std::cout << "Dependency Graph" << std::endl;
    myGraph.printNodes();
    myGraph.reverseDepend();
    myGraph.forestReverse();
    myGraph.forestForward();

    std::cout << "Rule Evaluation" << std::endl;
    myGraph.evaluateSCC();
    std::cout << std::endl;
    myGraph.evaluateAll();
//    myInterpreter.allRules(); //evaluates rules Lab4
//    myInterpreter.evaluateAll(); //evaluates queries

    delete lexer;

    return 0;
}