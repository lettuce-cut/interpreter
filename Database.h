#ifndef PROJECT_2_DATABASE_H
#define PROJECT_2_DATABASE_H

#include <map>
#include "Relation.h"
#include "Rule.h"

class Database {
private:
    std::vector<Predicate> schemesFromInterpreter;
    std::vector<Predicate> factsFromInterpreter;
    std::map<std::string, Relation> database;
    //map from name(string) to Relation
public:
    Database(std::vector<Predicate>& schemes, std::vector<Predicate>& facts);
    ~Database();
};

#endif //PROJECT_2_DATABASE_H
