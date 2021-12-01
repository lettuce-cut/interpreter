#ifndef PROJECT1_STARTER_CODE_QMARKAUTOMATON_H
#define PROJECT1_STARTER_CODE_QMARKAUTOMATON_H

#include "Automaton.h"

class QmarkAutomaton : public Automaton
{
public:
    QmarkAutomaton() : Automaton(TokenType::QMARK) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif //PROJECT1_STARTER_CODE_QMARKAUTOMATON_H
