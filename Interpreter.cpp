#include "Interpreter.h"
#include "Relation.h"
#include "Database.h"

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

void Interpreter::InterpreterRun() {
    std::cout << "Schemes(" << schemesFromParser.size() << "):" << std::endl;
    Predicate::stringPredicate(schemesFromParser, "Schemes");
    std::cout << "Facts(" << factsFromParser.size() << "):" << std::endl;
    Predicate::stringPredicate(factsFromParser, "Facts");
//    std::cout << "Queries(" << queriesFromParser.size() << "):" << std::endl;
//    Predicate::stringPredicate(queriesFromParser, "Queries");
}

void Interpreter::makeRelation() {
    std::cout << "Making Relations" << std::endl;
    for (int i = 0; i < schemesFromParser.size(); i++) {
        Relation toAdd = Relation(schemesFromParser[i].id, new Header(schemesFromParser[i].parameters));
        if (factsFromParser[i].id == toAdd.relationName) {
            Tuple newTuple = Tuple(factsFromParser[i].parameters);
            toAdd.addTuple(newTuple);
        }
    }

}

Interpreter::~Interpreter() = default;
