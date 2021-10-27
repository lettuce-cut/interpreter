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

void Relation::addTuple(Tuple toAdd) {
    relations.insert(toAdd);
}

void Relation::toString(std::set<Tuple> toPrint) {
    for (Tuple t : toPrint) {
        for (int i = 0; i < t.values.size(); i++){
            std::cout << t.values.at(i) << std::endl;
        }
    }
}
