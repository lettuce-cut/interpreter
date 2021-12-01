#ifndef AUTOMATON_H
#define AUTOMATON_H
#include "Token.h"
#include <iostream>
#include <utility>

class Automaton
{
protected:
    int inputRead;
    int newLines;
    long unsigned int index;
    TokenType type;

public:

    Automaton() : Automaton(TokenType::UNDEFINED) {}

    Automaton(TokenType type) { this->type = type;}

    int Start(const std::string& input) {
        newLines = 0;
        inputRead = 0;
        index = 0;
        if (input[0] == '\n') {
            newLines++;
        }
        S0(input);
        return inputRead;
    }

    virtual void S0(const std::string& input) = 0;

    void Serr() {
        inputRead = 0;
    }

    virtual Token* CreateToken(std::basic_string<char> input, int lineNumber) {
        return new Token(type, input, lineNumber);
    }

    int NewLinesRead() const { return newLines; }
};

#endif // AUTOMATON_H

