#include "Relation.h"
#include <map>

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

Relation Relation::SelectOne(int index, std::string value) {
//    std::cout << "PASSINGVALUES" << std::endl;
//    std::cout << value <<std::endl;
    Relation toChange = Relation();
    toChange.relationName = this->relationName;
    toChange.relationHeader = this->relationHeader;
    for (Tuple t : this->relations) {
//        std::cout << "TVALUES" << std::endl;
//        std::cout << t.values[index] <<std::endl;
        if (t.values[index] == value) {
            toChange.addTuple(t);
        }
    }
    return toChange;
}

Relation Relation::SelectTwo(int index, int indexTwo) {
    Relation toChange = Relation();
    toChange.relationName = this->relationName;
    toChange.relationHeader = this->relationHeader;
    std::map<std::string, std::string> checkOff;
    for (Tuple t : this->relations) {
        if (t.values[index] == t.values[indexTwo]) {
            checkOff[t.values[index]];
        }
    }
    return toChange;
}

Relation::Relation() = default;
