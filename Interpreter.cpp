#include "Interpreter.h"
#include "Relation.h"

Interpreter::Interpreter(DatalogProgram fromParser) {
    schemesFromParser = fromParser.getSchemes();
    factsFromParser = fromParser.getFacts();
    queriesFromParser = fromParser.getQueries();
}

void Interpreter::makeRelation() {
    for (int i = 0; i < schemesFromParser.size(); i++) {
        Relation toDatabase = Relation(schemesFromParser[i].id, Header(schemesFromParser[i].parameters));
        for (int j = 0; j < factsFromParser.size(); j++) {
            if (factsFromParser[j].id == schemesFromParser[i].id) {
                toDatabase.addTuple(factsFromParser[j].parameters);
            }
        }
        toDatabase.toString();
        myDatabase.addRelation(toDatabase);
    }
    std::cout << "Queries(" << queriesFromParser.size() << "):" << std::endl;
    Predicate::stringPredicate(queriesFromParser, "Queries");
}

Relation Interpreter::evaluatePredicate(Predicate p) {
    Relation toReturn = myDatabase.database[p.id];
    std::cout <<"THIS IS OG" << std::endl;
    toReturn.toString();
//    iterate through parameters, so index is i and value is value at i, and then adds
//    select two will compare the two values at the given index, and they equal it adds
    for (int i = 0; i < p.parameters.size(); i++) {
        if (p.parameters[i]->isConstant == true) {
            toReturn = toReturn.SelectOne(i, p.parameters[i]->paramString());
        }
        std::cout << "THIS IS SELECT ONE" << std::endl;
        toReturn.toString();
        for (int j = 0; j < p.parameters.size(); j++) {
            if ((i != j) and (p.parameters[i]->paramString() == p.parameters[j]->paramString())) {
                toReturn = toReturn.SelectTwo(i, j);
            }
        }
    }

    std::cout << "THIS IS SELECT TWO" << std::endl;
    toReturn.toString();
    return toReturn;
}

void Interpreter::evaluateAll() {
    for (int i = 0; i < queriesFromParser.size(); i++) {
        evaluatePredicate(queriesFromParser[i]);
    }
}

Interpreter::~Interpreter() = default;
