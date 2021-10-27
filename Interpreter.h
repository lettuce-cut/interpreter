#ifndef PROJECT_2_INTERPRETER_H
#define PROJECT_2_INTERPRETER_H

#include "Lexer.h"
#include "Relation.h"
#include "Predicate.h"

class Interpreter {
private:
public:
    void InterpreterRun();
    Relation* evaluatePredicate(const Predicate& p);
};


#endif //PROJECT_2_INTERPRETER_H
