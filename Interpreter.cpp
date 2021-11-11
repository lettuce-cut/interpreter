#include "Interpreter.h"
#include "Relation.h"

Interpreter::Interpreter(DatalogProgram fromParser) {
    schemesFromParser = fromParser.getSchemes();
    factsFromParser = fromParser.getFacts();
    queriesFromParser = fromParser.getQueries();
}

void Interpreter::makeRelation() {
    for (long unsigned int i = 0; i < schemesFromParser.size(); i++) {
        Relation toDatabase = Relation(schemesFromParser[i].id, Header(schemesFromParser[i].parameters));
        for (long unsigned int j = 0; j < factsFromParser.size(); j++) {
            if (factsFromParser[j].id == schemesFromParser[i].id) {
                toDatabase.addTuple(factsFromParser[j].parameters);
            }
        }
        myDatabase.addRelation(toDatabase);
    }
}

Relation Interpreter::evaluatePredicate(Predicate p) {
    Relation toReturn = myDatabase.database[p.id];
    std::vector<std::map<std::string, std::string>> tupleMaps;
    std::vector<int> indices;
    std::map<int, std::string> position;
    std::vector<std::string> forNames;


    for (long unsigned int i = 0; i < p.parameters.size(); i++) {
//        std::cout << p.parameters[i]->paramString() << std::endl;
        if (p.parameters[i]->isConstant == true) {
            toReturn = toReturn.SelectOne(i, p.parameters[i]->paramString());
//            std::cout << "DID SElECT ONE" << std::endl;
//            toReturn.toString();
        }
        else {//is a variable
            if (position.find(i)->first == 0) {
                position[i] = p.parameters[i]->paramString();
                indices.push_back(i);
            }
            else {
                for (long unsigned int m = 0; m < position.size(); m++) {
                    if (p.parameters[i]->paramString() == position[m]) {
                        toReturn = toReturn.SelectTwo(i, m);
//                        std::cout << "DID SElECT TWO" << std::endl;
//                        toReturn.toString();
                    }
                    else{
//                        forNames.push_back(p.parameters[i]->paramString());
                        position[i] = p.parameters[i]->paramString();
                        indices.push_back(i);
                    }
                }
            }
//            std::cout << "SIZE: " << indices.size() << std::endl;
        }
    }
    toReturn = toReturn.Project(indices);
//    std::cout << "DID PROJECT" << std::endl;
//    toReturn.toString();
    std::map<int, std::string>::iterator it;
    for (it = position.begin(); it != position.end(); it++) {
        if (forNames.size() == 0) {
            forNames.push_back(it->second);
        }
        else {
            int count = 0;
            for (std::string name : forNames) {
                if (name == it->second) {
                    count += 1;
                }
            }
            if (count == 0 and it->second != "") {
                forNames.push_back(it->second);
            }
        }
    }
//    for (std::string name : forNames) {
//        std::cout << "NAME: " << name << std::endl;
//    }
    toReturn = toReturn.Rename(forNames);
    return toReturn;
}

void Interpreter::evaluateAll() {
    for (long unsigned int i = 0; i < queriesFromParser.size(); i++) {
        Relation evaluated = evaluatePredicate(queriesFromParser[i]);
        std::cout << queriesFromParser[i].id << "(";
        for (long unsigned int j =0; j < queriesFromParser[i].parameters.size(); j++) {
            if (j == queriesFromParser[i].parameters.size() -1) {
                std::cout << queriesFromParser[i].parameters[j]->paramString() << ")?";
            }
            else {
                std::cout << queriesFromParser[i].parameters[j]->paramString() << ",";
            }
        }
        if (evaluated.relations.size() == 0) {
            std::cout << "No" << std::endl;
        }
        else {
            std::cout << " Yes(" << evaluated.relations.size() << ")" << std::endl;
            evaluated.toString();
        }
    }
}

Interpreter::~Interpreter() = default;
