#include "Rule.h"

void Rule::addBody(std::vector<Predicate> input) {
    bodyPredicates = input;
//    for (int i = 0; i < bodyPredicates.size(); i++) {
//        std::cout << "id: " << bodyPredicates.at(i).id << std::endl;
//        for (int j = 0; j < bodyPredicates.at(i).parameters.size(); j++) {
//            std::cout << bodyPredicates.at(i).parameters.at(j)->paramString() << std::endl;
//        }
//    }
}

void Rule::setHead(const Predicate& input) {
    headPredicate.id = input.id;
    headPredicate.parameters = input.parameters;
}

void Rule::ruleString(Rule input) {
        std::cout << input.headPredicate.id << "(";

        for (long unsigned int j = 0; j < input.headPredicate.parameters.size(); j++) {
            if (j == input.headPredicate.parameters.size()-1) {
                std::cout << input.headPredicate.parameters.at(j)->paramString() << ")";
            }
            else {
                std::cout << input.headPredicate.parameters.at(j)->paramString() << ",";
            }
        }

        std::cout << " :- ";


        for (long unsigned int k = 0; k < input.bodyPredicates.size(); k++) {
            std::cout << input.bodyPredicates.at(k).id << "(";

            for (long unsigned int h = 0; h < input.bodyPredicates.at(k).parameters.size(); h++) {
                if (h == input.bodyPredicates.at(k).parameters.size() - 1) {
                    std::cout << input.bodyPredicates.at(k).parameters.at(h)->paramString() << ")";
                } else {
                    std::cout << input.bodyPredicates.at(k).parameters.at(h)->paramString() << ",";
                }
            }
            if (k == input.bodyPredicates.size()-1) {
                std::cout << ".";
            }
            else {
                std::cout << ",";
            }
        }

        std::cout << std::endl;

}

Predicate Rule::getHead() {
    return headPredicate;
}

std::vector<Predicate> Rule::getBody() {
    return bodyPredicates;
}


Rule::~Rule()= default;

Rule::Rule() = default;

