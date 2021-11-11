#include "Relation.h"
#include <map>
#include "Interpreter.h"

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
        for (long unsigned int i = 0; i < relationHeader.attributes.size(); i++) {
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
    Relation toChange = Relation();
    toChange.relationName = this->relationName;
    toChange.relationHeader = this->relationHeader;
    for (Tuple t : this->relations) {
        if (t.values[index] == value) {
            toChange.addTuple(t);
        }
    }
    return toChange;
}

Relation Relation::Project(std::vector<int> forProject) {
    Relation toChange = Relation();
    for (int index : forProject) {
        toChange.relationHeader.attributes.push_back(this->relationHeader.attributes[index]);
    }
    for (Tuple t : this->relations) {
        Tuple newTuple;
        for (int index : forProject) {
            newTuple.values.push_back(t.values[index]);
        }
        toChange.addTuple(newTuple);
    }

    return toChange;
}

Relation Relation::Rename(std::vector<std::string> forRename) {
    Relation toChange = Relation();
    toChange.relationName = this->relationName;
    toChange.relations = this->relations;
    for (std::string name : forRename) {
        toChange.relationHeader.attributes.push_back(name);
    }

    return toChange;
}

Relation Relation::SelectTwo(int index, int indexTwo) {
    Relation toChange = Relation();
    toChange.relationName = this->relationName;
    toChange.relationHeader = this->relationHeader;
    for (Tuple t : this->relations) {
        if (t.values[index] == t.values[indexTwo]) {
            toChange.addTuple(t);
        }
    }
    return toChange;
}


Relation::Relation() = default;
