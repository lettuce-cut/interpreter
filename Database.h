#ifndef PROJECT_2_DATABASE_H
#define PROJECT_2_DATABASE_H

#include <map>
#include "Relation.h"
#include "Rule.h"

class Database {
private:
    std::vector<Predicate> schemesFromInterpreter;
    std::vector<Predicate> factsFromInterpreter;
    //map from name(string) to Relation
public:
    std::map<std::string, Relation> database;
    Database(Relation input);
    ~Database();
};

#endif //PROJECT_2_DATABASE_H
