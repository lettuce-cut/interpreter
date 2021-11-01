#ifndef PROJECT_2_HEADER_H
#define PROJECT_2_HEADER_H

#include <vector>
#include "Parameter.h"

class Header {
public:
    std::vector<std::string> attributes;

    Header(std::vector<Parameter *> input);
    ~Header();
};

#endif //PROJECT_2_HEADER_H
