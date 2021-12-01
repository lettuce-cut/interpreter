#ifndef PROJECT1_STARTER_CODE_MULTICOMMENT_H
#define PROJECT1_STARTER_CODE_MULTICOMMENT_H

#include "Automaton.h"

class MultiCommentAutomaton : public Automaton
{
private:
    void S1(const std::string& input);
    void S2(const std::string& input);
    void S3(const std::string& input);
    void S4(const std::string& input);

public:
    MultiCommentAutomaton() : Automaton(TokenType::MULTICOMMENT) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif //PROJECT1_STARTER_CODE_MULTICOMMENT_H
