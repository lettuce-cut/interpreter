#include "Parameter.h"
#include <typeinfo>
Parameter::Parameter(std::string input) {
    p = input;
    if (p[0] == '\'') {
        isConstant = true;
    }
//    std::cout<< "Parameter added: " << p << std::endl;
}

std::string Parameter::paramString() {
    return p;
}

Parameter::~Parameter() = default;
