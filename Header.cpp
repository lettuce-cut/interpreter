//
// Created by Sailor Ong on 10/26/21.
//

#include "Header.h"
#include <iostream>

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

Header::~Header() = default;
