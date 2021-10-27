#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include "Automaton.h"
#include "Token.h"

class Lexer
{
private:
    std::vector<Automaton*> automata;
    std::vector<Token*> tokens;

    void CreateAutomata();

    // TODO: add any other private methods here (if needed)

public:
    Lexer();
    ~Lexer();

    std::vector<Token*> Run(std::string& input);
    static void toString(std::vector<Token*> tokens) ;
    std::vector<Token*> getTokens();
    
    // TODO: add other public methods here

};

#endif // LEXER_H

