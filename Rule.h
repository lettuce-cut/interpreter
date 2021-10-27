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
    static void ruleString(std::vector<Rule> input);

    Rule();

    void setHead(const Predicate& input);
};

#endif //PROJECT_2_RULE_H
