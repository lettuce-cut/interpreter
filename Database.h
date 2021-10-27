#ifndef PROJECT_2_DATABASE_H
#define PROJECT_2_DATABASE_H

#include <map>
#include "Relation.h"

class Database {
private:
    std::map<std::string, Relation> database;
    //map from name(string) to Relation
public:
};

#endif //PROJECT_2_DATABASE_H
