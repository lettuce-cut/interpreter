#include "Database.h"

//Database::Database(std::vector<Predicate>& schemes, std::vector<Predicate>& facts) {
//    schemesFromInterpreter = schemes;
//    factsFromInterpreter = facts;
//}

Database::Database() = default;

void Database::addRelation(Relation toInsert) {
    database[toInsert.relationName] = toInsert;

}

Database::~Database() = default;
