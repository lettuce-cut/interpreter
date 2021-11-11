#ifndef PROJECT_2_INTERPRETER_H
#define PROJECT_2_INTERPRETER_H

#include "Lexer.h"
#include "Relation.h"
#include "Rule.h"
#include "DatalogProgram.h"
#include "Database.h"
#include <list>

class Interpreter {
private:
    std::vector<Predicate> schemesFromParser;
    std::vector<Predicate> factsFromParser;
    std::vector<Predicate> queriesFromParser;
    std::vector<Rule> rulesFromParser;
public:
    Database myDatabase;
    Interpreter(DatalogProgram fromParser);
    ~Interpreter();

    void makeRelation();
    Relation evaluatePredicate(Predicate p);
    void evaluateAll();
};


#endif //PROJECT_2_INTERPRETER_H
