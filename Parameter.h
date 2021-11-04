#ifndef PROJECT_2_PARAMETER_H
#define PROJECT_2_PARAMETER_H

#include <vector>
#include <iostream>

class Parameter {
private:
    std::string p;
    char a;
public:
    bool isConstant;
    Parameter(std::string input);
    ~Parameter();
    std::string paramString();
};

#endif //PROJECT_2_PARAMETER_H
