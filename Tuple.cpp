#include "Tuple.h"

Tuple::Tuple(std::vector<Parameter *> input) {
    for (int i = 0; i < input.size(); i++) {
        values.push_back(input[i]->paramString());
    }
}

Tuple::Tuple() = default;

Tuple::~Tuple() = default;
