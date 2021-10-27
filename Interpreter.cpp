#include "Interpreter.h"

Interpreter::Interpreter(std::vector<Predicate>& schemes, std::vector<Predicate>& facts, std::vector<Predicate>& queries,
                         std::vector<Rule>& rules) {
    schemesFromParser = schemes;
    factsFromParser = facts;
    queriesFromParser = queries;
    rulesFromParser = rules;
}

std::vector<Predicate> Interpreter::getSchemes() {
    return schemesFromParser;
}

std::vector<Predicate> Interpreter::getFacts() {
    return factsFromParser;
}

Interpreter::~Interpreter() = default;
