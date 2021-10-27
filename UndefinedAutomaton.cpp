#include "UndefinedAutomaton.h"
#include <iostream>
void UndefinedAutomaton::S0(const std::string& input) {
    if (index < input.size()) {
        inputRead++;
        index++;
        S0(input);
    }
}