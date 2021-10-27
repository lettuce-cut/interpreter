#ifndef PROJECT_2_TUPLE_H
#define PROJECT_2_TUPLE_H

#include <iostream>
#include <vector>

class Tuple {
private:
public:
    std::vector<std::string> values;
    bool operator<(const Tuple &rhs) const {
        return values < rhs.values;
    }
};

#endif //PROJECT_2_TUPLE_H
