#include "ColonDashAutomaton.h"
#include <iostream>

void ColonDashAutomaton::S0(const std::string& input) {
    if (input[0] == ':') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void ColonDashAutomaton::S1(const std::string& input) {
    if (input[1] == '-') {
        inputRead++;
    }
    else {
        Serr();
    }
}