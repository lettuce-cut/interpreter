#ifndef PROJECT1_STARTER_CODE_EOFAUTOMATON_H
#define PROJECT1_STARTER_CODE_EOFAUTOMATON_H

#include "Automaton.h"

class EOFAutomaton : public Automaton
{
private:
    void S1(const std::string& input);
public:
    EOFAutomaton() : Automaton(TokenType::END) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif //PROJECT1_STARTER_CODE_EOFAUTOMATON_H
