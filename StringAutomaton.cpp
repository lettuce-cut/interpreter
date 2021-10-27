#include "StringAutomaton.h"
#include <iostream>

void StringAutomaton::S0(const std::string& input) {
    if (input[index] == '\'') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void StringAutomaton::S1(const std::string& input) {
    if (index >= input.size()){
        type = TokenType::UNDEFINED;
    }
    else if (input[index] == '\'') {
        inputRead++;
        index++;
        S2(input);
    }
    else if (input[index] != '\''){
        inputRead++;
        index++;
        S1(input);
    }
}

void StringAutomaton::S2(const std::string& input) {
    if (input[index] == '\'') {
        inputRead++;
        index++;
        S1(input);
    }

}


//void StringAutomaton::S1(const std::string &input) {
//    if (input[index] == '\'') {
//        if (input[index+1] == '\'') {
//            inputRead++;
//            index++;
//            S1(input);
//        }
//        else if (std::isalnum(input[index+1]) == true) {
//            inputRead++;
//            index++;
//            S1(input);
//        }
//        else if(input[index+1] == '\n') {
//            inputRead++;
//            index++;
//            S1(input);
//        }
//        else {
//            inputRead++;
//        }
//    }
//    else if (input[index] !='\'') {
//        inputRead++;
//        index++;
//        S1(input);
//    }
//    else {
//        Serr();
//    }
//}

//void StringAutomaton::Loop(const std::string &input) {
//    if (input[index] != '\'') {
//        inputRead++;
//        index++;
//        S1(input);
//    }
//    else{
//        Serr();
//    }
//}