#include "Parameter.h"

Parameter::Parameter(std::string input) {
    p = input;
//    std::cout<< "Parameter added: " << p << std::endl;
}

std::string Parameter::paramString() {
    return p;
}

Parameter::~Parameter() {

}
