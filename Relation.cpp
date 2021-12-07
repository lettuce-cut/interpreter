#include "Relation.h"
#include <map>
Relation::Relation(std::string name, Header header) {
    relationName = name;
    relationHeader.attributes= header.attributes;
    relations = {};
}

Relation::~Relation() = default;

void Relation::addTuple(Tuple toAdd) {
    relations.insert(relations.end(), toAdd);
}

void Relation::toString() {
    for (Tuple t : relations) {
        std::cout << "  ";
        for (long unsigned int i = 0; i < relationHeader.attributes.size(); i++) {
            if (i < relationHeader.attributes.size()-1) {
                std::cout << relationHeader.attributes[i] << "=" << t.values[i] << ", ";
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
//        for (int i =0; i < t.values.size(); i++) {
//            std::cout << t.values[i] << std::endl;
//        }
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
    for (Tuple t : this->relations) {
        if (t.values[index] == t.values[indexTwo]) {
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

Relation Relation::Rename(std::vector<std::string> forRename) const {
//    std::cout << "IN RENAME" << std::endl;
//    this->toString();
    Relation toChange = Relation();
    toChange.relationName = this->relationName;
    toChange.relations = this->relations;
    for (std::string name : forRename) {
        toChange.relationHeader.attributes.push_back(name);
    }

    return toChange;
}

Relation Relation::Join(Relation joinWith) {
//
//    std::cout << "IN JOIN" << std::endl;
//    this->toString();
//    std::cout << std::endl;
//    joinWith.toString();
//    std::cout << std::endl;

    Relation isJoining = Relation();
    bool canJoin;
    std::map<int, int> indices;
    Tuple tupleOne;
    Tuple tupleTwo;
    Tuple toAdd;

//    std::cout << "INDEX CHECK::\n";
//    for (int i =0; i < indices.size(); i++) {
//        std::cout << "INDEX:: " << indices[i] << std::endl;
//    }

    isJoining.relationHeader = this->relationHeader.combineHeaders(joinWith.relationHeader, indices);
//    std::cout << "COMBIEND HEADER" << std::endl;
//    isJoining.relationHeader.toString();

    if (isJoining.relationHeader.attributes == this->relationHeader.attributes) {
        for (Tuple t : this->relations) {
            for (Tuple u : joinWith.relations) {
                if (u.values == t.values) {
                    toAdd = t;
                    isJoining.addTuple(toAdd);
                }
            }
        }
    }
    else {
        for (Tuple t : this->relations) {
            for (Tuple u : joinWith.relations) {
                canJoin = isJoinable(t, u, indices);
                if (canJoin == true) {
                    toAdd = combineTuples(t, u, indices, isJoining.relationHeader.attributes.size());
                    isJoining.addTuple(toAdd);
                }
            }
        }
    }
    return isJoining;
}

bool Relation::isJoinable(Tuple firstTuple, Tuple secondTuple, std::map<int, int>& indices) {
//    std::cout << "CANJOIN" << std::endl;
    bool toReturn = false;
    long unsigned int counter = 0;

    if (indices.size() == 0) {
        toReturn = true;
    }


    else {
        std::map<int, int>:: iterator it;

        for (it = indices.begin(); it != indices.end(); it++) {
            if (firstTuple.values[it->second] == secondTuple.values[it->first]) {
                counter += 1;
            }
        }

        if (counter > 0) {
            toReturn = true;
        }
    }
    return toReturn;
}

Tuple Relation::combineTuples(Tuple firstTuple, Tuple secondTuple, std::map<int, int>& indices, long unsigned int headerCount) {
//    std::cout << "IN COMBINE" << std::endl;
    Tuple toReturn = Tuple();

    for (const auto & value : secondTuple.values) {
        toReturn.values.push_back(value);
    }

    for (long unsigned int i = 0; i < firstTuple.values.size(); i++) {
//        std::cout << "FIRST TUPLE: " << firstTuple.values[i] << std::endl;
        if (headerCount == (firstTuple.values.size() + secondTuple.values.size())) {
            toReturn.values.push_back(firstTuple.values[i]);
        }
        else {
            std::map<int, int>::iterator it;
//            std::cout << "TEST" << std::endl;
            for (it = indices.begin(); it != indices.end(); it++) {
                if (firstTuple.values[i] == firstTuple.values[it->second]) {
//                    std::cout << it->first << ':' << it->second << std::endl;
                    toReturn.values.push_back(firstTuple.values[i+1]);
                }
                else {
                    if (toReturn.values[toReturn.values.size()-1] != firstTuple.values[i]){
                        toReturn.values.push_back(firstTuple.values[i]);
                    }
                }
            }
//           if (firstTuple.values[i] != toReturn.values[toReturn.values.size()-1]) {
//                toReturn.values.push_back(firstTuple.values[i]);
//            }
        }
//    std::cout <<"TEST" <<std::endl;
//    for (int i =0; i < toReturn.values.size(); i++) {
//        std::cout << toReturn.values[i] << " ";
//    }
//    std::cout << std::endl;
    }

    return toReturn;
}

Relation Relation::Uniter(Relation toUnite, std::set<Tuple>& relationsAdded) {

    for (Tuple t : this->relations) {
        if(toUnite.relations.find(t) != toUnite.relations.end()) {
            toUnite.addTuple(t);
        }
        else {
            relationsAdded.insert(t);
            toUnite.addTuple(t);
        }
    }

    return toUnite;
}

Relation::Relation() = default;
