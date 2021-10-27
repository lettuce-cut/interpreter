#ifndef PROJECT_2_PREDICATE_H
#define PROJECT_2_PREDICATE_H

#include <vector>
#include <iostream>
#include "Parameter.h"
#include "Token.h"

class Predicate {
public:
    Predicate(Token *input);
    Predicate(std::string name) { this->id = name; }

    Predicate(Predicate *pPredicate);

    ~Predicate();
    Predicate();
    std::string id;
    std::vector<Parameter*> parameters;


    void addParameter(std::vector<Parameter*> input);
    static void stringPredicate(std::vector<Predicate> input, std::string punct);



};

#endif //PROJECT_2_PREDICATE_H
