//
// Created by Sailor Ong on 10/26/21.
//

#include "Header.h"
#include <iostream>
#include <set>

Header::Header(std::vector<Parameter *> input) {
    for (long unsigned int i = 0; i < input.size(); i++) {
        attributes.push_back(input[i]->paramString());
    }
}

Header::Header() = default;

void Header::toString() {
    for (long unsigned int i = 0; i < attributes.size(); i++) {
        std::cout << attributes[i] << std::endl;
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

    for (long unsigned int i =0; i < headerToJoin.attributes.size(); i++) {
        if (toReturn.attributes.size() == 0) {
            toReturn.attributes.push_back(headerToJoin.attributes[i]);
        } else {
            int firstCounter = 0;
            for (long unsigned int j = 0; j < toReturn.attributes.size(); j++) {
                if (headerToJoin.attributes[i] == toReturn.attributes[j]) {
                    firstCounter += 1;
                }
            }
            if (firstCounter == 0) {
                toReturn.attributes.push_back(headerToJoin.attributes[i]);
            }
        }
    }

    for (long unsigned int i =0; i < this->attributes.size(); i++) {
        if (toReturn.attributes.size() == 0) {
            toReturn.attributes.push_back(this->attributes[i]);
        }
        else {
            int firstCounter = 0;
            for (long unsigned int j = 0; j < toReturn.attributes.size(); j++) {
                if (this->attributes[i] == toReturn.attributes[j]) {
                    firstCounter += 1;
                }
            }
            if (firstCounter == 0) {
                toReturn.attributes.push_back(this->attributes[i]);
            }
        }
    }

    for (long unsigned int i =0; i < headerToJoin.attributes.size(); i++) {
        for (long unsigned int j =0; j < this->attributes.size(); j++) {
            if (headerToJoin.attributes[i] == this->attributes[j]){
                indices[i] = j;
            }
        }
    }

    return toReturn;
}


Header::~Header() = default;
