#ifndef PROJECT_2_TUPLE_H
#define PROJECT_2_TUPLE_H

#include <iostream>
#include <vector>
#include "Parameter.h"
class Tuple {
public:
    std::vector<std::string> values;
    Tuple(std::vector<Parameter *> input);
    Tuple();
    ~Tuple();

    bool operator<(const Tuple &rhs) const {
        return values < rhs.values;
    }
};

#endif //PROJECT_2_TUPLE_H
