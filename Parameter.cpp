#include "Parameter.h"
#include <typeinfo>
Parameter::Parameter(std::string input) {
    p = input;
    a = p.at(0);
    if (a == '\'') {
        isConstant = true;
    }
//    std::cout<< "Parameter added: " << p << std::endl;
}

std::string Parameter::paramString() {
    return p;
}

Parameter::~Parameter() = default;
