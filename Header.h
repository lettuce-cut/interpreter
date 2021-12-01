#ifndef PROJECT_2_HEADER_H
#define PROJECT_2_HEADER_H

#include <vector>
#include "Parameter.h"
#include <map>

class Header {
public:
    std::vector<std::string> attributes;
    Header(std::vector<Parameter *> input);
    Header();
    ~Header();
    void toString();

    Header combineHeaders(Header headerToJoin, std::map<int, int>& indices);
};

#endif //PROJECT_2_HEADER_H
