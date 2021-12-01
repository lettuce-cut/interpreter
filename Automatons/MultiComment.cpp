#include "MultiComment.h"

void MultiCommentAutomaton::S0(const std::string& input) {
    if (input[index] == '#') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void MultiCommentAutomaton::S1(const std::string& input) {
    if (input[index] == EOF){
        Serr();
    }
    else if (input[index] == '|') {
        inputRead++;
        index++;
        S2(input);
    }
}
void MultiCommentAutomaton::S2(const std::string& input) {
    if (index >= input.size()) {
        Serr();
    }
    else if (input[index] == '|') {
        inputRead++;
        index++;
        S3(input);
    }
    else {
        inputRead++;
        index++;
        S2(input);
    }
}

void MultiCommentAutomaton::S3(const std::string& input) {
    if (input[index] == EOF) {
        Serr();
    }
    else if (input[index] == '#') {
        inputRead++;
        type = TokenType::COMMENT;
    }
    else if (input[index] == '\n'){
            inputRead++;
            index++;
            S2(input);
        }
    else {
        inputRead++;
        index++;
        S1(input);
        type = TokenType::UNDEFINED;
    }
}





//Below is for the combined comment automaton that was working the best
//void CommentAutomaton::S0(const std::string& input) {

//    if (input[index] == '#') {
//        inputRead++;
//        index++;
//        S1(input);
//    }
//    else {
//        Serr();
//    }
//}
//
//void CommentAutomaton::S1(const std::string& input) {
//    if (input[index] == '|') {
//        inputRead++;
//        index++;
//        S2(input);
//    }
//    else if (input[index] == '\n'){
//        inputRead++;
//    }
//    else {
//        inputRead++;
//        index++;
//        S1(input);
//
//    }
//}
//void CommentAutomaton::S2(const std::string& input) {
//    if (input[index] == '|') {
//        inputRead++;
//        index++;
//        S3(input);
//    }
//    else {
//        S2(input);
//    }
//}
//void CommentAutomaton::S3(const std::string& input) {
//    if (input[index] == '#') {
//        inputRead++;
//        index++;
//        S4(input);
//    }
//    else {
//        S2(input);
//    }
//}
//void CommentAutomaton::S4(const std::string& input) {
//    if (input[index] == '\n') {
//        inputRead++;
//    }
//    else {
//        S2(input);
//    }
//}


