#include "Database.h"

//Database::Database(std::vector<Predicate>& schemes, std::vector<Predicate>& facts) {
//    schemesFromInterpreter = schemes;
//    factsFromInterpreter = facts;
//}

Database::Database(Relation input) {
    database.insert( std::pair<std::string, Relation> (input.relationName, input));
    std::cout << "relation stored" << std::endl;
}

Database::~Database() = default;
