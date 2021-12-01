#ifndef PROJECT_2_RULE_H
#define PROJECT_2_RULE_H

#include <vector>
#include <iostream>
#include "Predicate.h"

class Rule {
private:
    Predicate headPredicate;
    std::vector<Predicate> bodyPredicates;
public:
    ~Rule();
    void addBody(std::vector<Predicate> input);
    static void ruleString(Rule input);

    Rule();

    void setHead(const Predicate& input);
    Predicate getHead();
    std::vector<Predicate> getBody();
};

#endif //PROJECT_2_RULE_H
