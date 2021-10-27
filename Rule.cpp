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

void Rule::ruleString(std::vector<Rule> input) {
    for (long unsigned int i = 0; i < input.size(); i++) {
        std::cout << "  " << input.at(i).headPredicate.id << "(";

        for (long unsigned int j = 0; j < input.at(i).headPredicate.parameters.size(); j++) {
            if (j == input.at(i).headPredicate.parameters.size()-1) {
                std::cout << input.at(i).headPredicate.parameters.at(j)->paramString() << ")";
            }
            else {
                std::cout << input.at(i).headPredicate.parameters.at(j)->paramString() << ",";
            }
        }

        std::cout << " :- ";


        for (long unsigned int k = 0; k < input.at(i).bodyPredicates.size(); k++) {
            std::cout << input.at(i).bodyPredicates.at(k).id << "(";

            for (long unsigned int h = 0; h < input.at(i).bodyPredicates.at(k).parameters.size(); h++) {
                if (h == input.at(i).bodyPredicates.at(k).parameters.size() - 1) {
                    std::cout << input.at(i).bodyPredicates.at(k).parameters.at(h)->paramString() << ")";
                } else {
                    std::cout << input.at(i).bodyPredicates.at(k).parameters.at(h)->paramString() << ",";
                }
            }
            if (k == input.at(i).bodyPredicates.size()-1) {
                std::cout << ".";
            }
            else {
                std::cout << ",";
            }
        }

        std::cout << std::endl;
    }

}


Rule::~Rule()= default;

Rule::Rule() = default;

