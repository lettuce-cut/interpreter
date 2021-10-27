#include "Relation.h"

Relation Relation::SelectOne(int index, std::string value) {
    return Relation();
}

Relation Relation::SelectTwo(int index, int indexTwo) {
    return Relation();
}

Relation Relation::Project(std::list<int> forProject) {
    return Relation();
}

Relation Relation::Rename(std::list<std::string> forRename) {
    return Relation();
}

Relation::Relation() {
    relationName = "";
    relationHeader->attributes = {};
    relations = {};
}

Relation::~Relation() {

}