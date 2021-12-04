//
// Created by Sailor Ong on 10/26/21.
//

#include "Header.h"
#include <iostream>

Header::Header(std::vector<Parameter *> input) {
    for (auto & i : input) {
        attributes.push_back(i->paramString());
    }
}

Header::Header() = default;

void Header::toString() {
    for (auto & attribute : attributes) {
        std::cout << attribute << std::endl;
    }
}

Header Header::combineHeaders(Header headerToJoin, std::map<int, int>& indices) {
//    std::cout << "IN COMBINE HEADER" << std::endl;
    Header toReturn = Header();
//
//    std::cout << "woeicfe," << std::endl;
//    this->toString();
//    std::cout << "woeicfe," << std::endl;
//    headerToJoin.toString();
//    std::cout << std::endl;

    for (auto & attribute : headerToJoin.attributes) {
        if (toReturn.attributes.empty()) {
            toReturn.attributes.push_back(attribute);
        } else {
            int firstCounter = 0;
            for (auto & j : toReturn.attributes) {
                if (attribute == j) {
                    firstCounter += 1;
                }
            }
            if (firstCounter == 0) {
                toReturn.attributes.push_back(attribute);
            }
        }
    }

    for (auto & attribute : this->attributes) {
        if (toReturn.attributes.empty()) {
            toReturn.attributes.push_back(attribute);
        }
        else {
            int firstCounter = 0;
            for (auto & j : toReturn.attributes) {
                if (attribute == j) {
                    firstCounter += 1;
                }
            }
            if (firstCounter == 0) {
                toReturn.attributes.push_back(attribute);
            }
        }
    }

    for (long unsigned int i =0; i < headerToJoin.attributes.size(); i++) {
        for (long unsigned int j =0; j < this->attributes.size(); j++) {
            if (headerToJoin.attributes[i] == this->attributes[j]){
                indices[i] = j;
//                std::cout << i << " + " << indices[i] << std::endl;
            }
        }
    }

    return toReturn;
}


Header::~Header() = default;
