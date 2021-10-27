#include "Database.h"

Database::Database(std::vector<Predicate>& schemes, std::vector<Predicate>& facts) {
    schemesFromInterpreter = schemes;
    factsFromInterpreter = facts;
}

Database::~Database() = default;
