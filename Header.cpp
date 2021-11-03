//
// Created by Sailor Ong on 10/26/21.
//

#include "Header.h"
#include <iostream>

Header::Header(std::vector<Parameter *> input) {
    for (int i = 0; i < input.size(); i++) {
        attributes.push_back(input[i]->paramString());
    }
}

Header::Header() {}

Header::~Header() = default;
