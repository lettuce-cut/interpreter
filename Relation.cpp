#include "Relation.h"

//Relation Relation::SelectOne(int index, std::string value) {
//    return Relation();
//}
//
//Relation Relation::SelectTwo(int index, int indexTwo) {
//    return Relation();
//}
//
//Relation Relation::Project(std::list<int> forProject) {
//    return Relation();
//}
//
//Relation Relation::Rename(std::list<std::string> forRename) {
//    return Relation();
//}

Relation::Relation(std::string name, Header header) {
    relationName = name;
    relationHeader.attributes= header.attributes;
    relations = {};
}

Relation::~Relation() = default;

void Relation::addTuple(Tuple toAdd) {
    relations.insert(toAdd);
}

void Relation::toString() {
    for (Tuple t : relations) {
        for (int i = 0; i < relationHeader.attributes.size(); i++) {
            if (i < relationHeader.attributes.size()-1) {
                std::cout << relationHeader.attributes[i] << "=" << t.values[i] << ",";
            }
            else {
                std::cout << relationHeader.attributes[i] << "=" << t.values[i] << std::endl;
            }
        }
    }
}

Relation::Relation() = default;
