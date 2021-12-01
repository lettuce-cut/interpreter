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

//    std::cout << "woeicfe," << std::endl;
//    this->toString();
//    std::cout << "woeicfe," << std::endl;
//    headerToJoin.toString();
//    std::cout << std::endl;

    for (long unsigned int i =0; i < headerToJoin.attributes.size(); i++){
        if (toReturn.attributes.size() ==0) {
            toReturn.attributes.push_back(headerToJoin.attributes[i]);
        }
        else {
            int firstCounter = 0;
            for (long unsigned int m =0; m < toReturn.attributes.size(); m++) {
                if (headerToJoin.attributes[i] == toReturn.attributes[m]){
                    firstCounter += 1;
                }
            }
            if (firstCounter ==0) {
                toReturn.attributes.push_back(headerToJoin.attributes[i]);
            }
        }
        int counter = 0;
        for (long unsigned int j =0; j < this->attributes.size(); j++){
//            std::cout << headerToJoin.attributes[i] << " + " << this->attributes[j] << std::endl;
            if (headerToJoin.attributes[i] == this->attributes[j]){
//                std::cout << i << " + " << j << std::endl;
                indices[i] = j;
                counter += 1;
            }
            if (counter == 0) {
                toReturn.attributes.push_back(this->attributes[j]);
//                std::cout << this->attributes[j] << std::endl << std::endl;
            }
        }

    }

    return toReturn;
}


Header::~Header() = default;
