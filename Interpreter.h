#ifndef PROJECT_2_INTERPRETER_H
#define PROJECT_2_INTERPRETER_H

#include "Lexer.h"
#include "Relation.h"
#include "Rule.h"

class Interpreter {
private:
    std::vector<Predicate> schemesFromParser;
    std::vector<Predicate> factsFromParser;
    std::vector<Predicate> queriesFromParser;
    std::vector<Rule> rulesFromParser;
public:
    Interpreter(std::vector<Predicate>& schemes, std::vector<Predicate>& facts, std::vector<Predicate>& queries, std::vector<Rule>& rules);
    ~Interpreter();

    std::vector<Predicate> getSchemes();
    std::vector<Predicate> getFacts();

    void InterpreterRun();
    void makeRelation();

//    Relation* evaluatePredicate(const Predicate& p);
};


#endif //PROJECT_2_INTERPRETER_H
