#ifndef PROJECT_2_DATABASE_H
#define PROJECT_2_DATABASE_H

#include <map>
#include "Relation.h"
#include "Rule.h"

class Database {
public:
    std::map<std::string, Relation> database;
    Database();
    ~Database();
    void addRelation(Relation toInsert);
};

#endif //PROJECT_2_DATABASE_H
