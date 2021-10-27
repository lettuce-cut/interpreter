#include "DatalogProgram.h"
#include "Token.h"
#include "Predicate.h"
std::vector<Parameter*> toPass;
std::vector<Predicate> toPassPred;
std::vector<Predicate> vectorSchemes;
std::vector<Predicate> vectorQueries;
std::vector<Predicate> vectorFacts;

Predicate pSchemes;
Predicate pQueries;
Predicate pFacts;

std::vector<Rule> vectorRules;
Rule rRules;
//Predicate pRulesHead;
std::vector<Predicate> vectorBodyPred;
Predicate pRules;



void DatalogProgram::parseRun(const std::vector<Token*>& toParse) {
//    Match(toParse.at(index), TokenType::SCHEMES);
//    Match(toParse.at(index), TokenType::COLON);
    datalogProgramParse(toParse);
}
void DatalogProgram::Match(Token *pToken, TokenType tokenType) {
    if (pToken->type == tokenType) {
        index++;
    }
    else {
        std::string error = pToken->toString();
        throw error;
    }
}

void DatalogProgram::datalogProgramParse(std::vector<Token*> toParse) {
    Match(toParse.at(index), TokenType::SCHEMES);
    Match(toParse.at(index), TokenType::COLON);
    schemeParse(toParse);
    schemeListPars(toParse);
    Match(toParse.at(index), TokenType::FACTS);
    Match(toParse.at(index), TokenType::COLON);
    factListParse(toParse);
    Match(toParse.at(index), TokenType::RULES);
    Match(toParse.at(index), TokenType::COLON);
    ruleListParse(toParse);
    Match(toParse.at(index), TokenType::QUERIES);
    Match(toParse.at(index), TokenType::COLON);
    queryParse(toParse);
    queryListParse(toParse);
    Match(toParse.at(index), TokenType::END); //Make an END function with all the correct output
}




void DatalogProgram::schemeListPars(const std::vector<Token*>& toParse) {
    if (toParse.at(index)->type == TokenType::ID) {
        schemeParse(toParse);
        schemeListPars(toParse);
    }
}
void DatalogProgram::factListParse(const std::vector<Token*>& toParse) {
    if (toParse.at(index)->type == TokenType::ID) {
        factParse(toParse);
        factListParse(toParse);
    }
}
void DatalogProgram::ruleListParse(const std::vector<Token*>& toParse) {
    if (toParse.at(index)->type == TokenType::ID) {
        ruleParse(toParse);
        ruleListParse(toParse);
    }
}
void DatalogProgram::queryListParse(const std::vector<Token*>& toParse) {
    if (toParse.at(index)->type == TokenType::ID) {
        queryParse(toParse);
        queryListParse(toParse);
    }
}
void DatalogProgram::schemeParse(std::vector<Token*> toParse) {
    Match(toParse.at(index), TokenType::ID);
    pSchemes.id = toParse.at(index-1)->value;
//    std::cout << pSchemes.id << std::endl;
    Match(toParse.at(index), TokenType::LEFT_PAREN);
    Match(toParse.at(index), TokenType::ID);
    toPass.push_back(new Parameter(toParse.at(index-1)->value));//stored
    idListParse(toParse);
    Match(toParse.at(index), TokenType::RIGHT_PAREN);
    pSchemes.addParameter(toPass);
    vectorSchemes.push_back(pSchemes);
    toPass.clear();
}

void DatalogProgram::factParse(std::vector<Token*> toParse) {
    Match(toParse.at(index), TokenType::ID);
    pFacts.id = toParse.at(index-1)->value;
//    std::cout << pFacts.id << std::endl;
    Match(toParse.at(index), TokenType::LEFT_PAREN);
    Match(toParse.at(index), TokenType::STRING);
    toPass.push_back(new Parameter(toParse.at(index-1)->value));//stored
    stringList(toParse);
    Match(toParse.at(index), TokenType::RIGHT_PAREN);
    Match(toParse.at(index), TokenType::PERIOD);
    pFacts.addParameter(toPass);
    setDomain(toPass);
    vectorFacts.push_back(pFacts);
    toPass.clear();
}

//Work on this Function
void DatalogProgram::ruleParse(std::vector<Token*> toParse) {
    headPredicateParse(toParse);
    Match(toParse.at(index), TokenType::COLON_DASH);
    predicateParseRules(toParse);
    predicateListParse(toParse);
    Match(toParse.at(index),TokenType::PERIOD);

    rRules.addBody(vectorBodyPred);
    vectorBodyPred.clear();
    vectorRules.push_back(rRules);
}



void DatalogProgram::queryParse(std::vector<Token*> toParse) {
    pQueries.id = toParse.at(index)->value;
//    std::cout << pQueries.id << std::endl;
    predicateParse(toParse);
    Match(toParse.at(index), TokenType::QMARK);
    pQueries.addParameter(toPass);
    vectorQueries.push_back(pQueries);
    toPass.clear();
}


//Work on this function
void DatalogProgram::headPredicateParse(std::vector<Token*> toParse) {
    Match(toParse.at(index), TokenType::ID);
    pSchemes.id = toParse.at(index-1)->value;
//    std::cout << pRulesHead.id << std::endl;
    Match(toParse.at(index), TokenType::LEFT_PAREN);
    Match(toParse.at(index), TokenType::ID);
    toPass.push_back(new Parameter(toParse.at(index-1)->value));
    idListParse(toParse);
    Match(toParse.at(index), TokenType::RIGHT_PAREN);
    pSchemes.addParameter(toPass);

    for (long unsigned int i = 0; i < vectorSchemes.size(); i++) {
        long unsigned int count = 0;
        if (pSchemes.id != vectorSchemes.at(i).id) {
            count ++;
            if (count == vectorSchemes.size()) {
                vectorSchemes.push_back(pSchemes);
            }
        }
    }
    rRules.setHead(pSchemes);
    toPass.clear();
}


void DatalogProgram::predicateParse(std::vector<Token*> toParse) {
    Match(toParse.at(index), TokenType::ID);
    Match(toParse.at(index), TokenType::LEFT_PAREN);
    parameterParse(toParse);
    parameterList(toParse);
    Match(toParse.at(index), TokenType::RIGHT_PAREN);
}

void DatalogProgram::predicateParseRules(std::vector<Token*> toParse) {
    pRules.id = toParse.at(index)->value;
    Match(toParse.at(index), TokenType::ID);
    Match(toParse.at(index), TokenType::LEFT_PAREN);
    parameterParse(toParse);
    parameterList(toParse);
    pRules.addParameter(toPass);
    Match(toParse.at(index), TokenType::RIGHT_PAREN);
    toPass.clear();
    vectorBodyPred.push_back(pRules);
}

//Work on this function
void DatalogProgram::predicateListParse(std::vector<Token*> toParse) {
    if (toParse.at(index)->type == TokenType::COMMA) {
        Match(toParse.at(index), TokenType::COMMA);
        predicateParseRules(toParse);
        predicateListParse(toParse);
    }
}


void DatalogProgram:: parameterList(std::vector<Token*> toParse) {
    if (toParse.at(index)->type == TokenType::COMMA) {
        Match(toParse.at(index), TokenType::COMMA);
        parameterParse(toParse);
        parameterList(toParse);
    }
}
void DatalogProgram::stringList(std::vector<Token*> toParse) {
    if (toParse.at(index)->type == TokenType::COMMA) {
        Match(toParse.at(index), TokenType::COMMA);
        Match(toParse.at(index), TokenType::STRING);
        toPass.push_back(new Parameter(toParse.at(index-1)->value));//stored
        stringList(toParse);
    }
}
void DatalogProgram::idListParse(std::vector<Token*> toParse) {
    if (toParse.at(index)->type == TokenType::COMMA) {
        Match(toParse.at(index), TokenType::COMMA);
        Match(toParse.at(index), TokenType::ID);
        toPass.push_back(new Parameter(toParse.at(index-1)->value));
        idListParse(toParse);
    }
}
void DatalogProgram::parameterParse(std::vector<Token*> toParse) {
    if (toParse.at(index)->type != TokenType::END) {

        if (toParse.at(index)->type == TokenType::STRING) {
            Match(toParse.at(index), TokenType::STRING);
            toPass.push_back(new Parameter(toParse.at(index - 1)->value));//stored
        } else {
            Match(toParse.at(index), TokenType::ID);
            toPass.push_back(new Parameter(toParse.at(index - 1)->value));//stored
        }
    }
}

void DatalogProgram::outputString(){
    std::cout << "Schemes(" << vectorSchemes.size() << "):" << std::endl;
    Predicate::stringPredicate(vectorSchemes, "Schemes");
    std::cout << "Facts(" << vectorFacts.size() << "):" << std::endl;
    Predicate::stringPredicate(vectorFacts, "Facts");
    std::cout << "Rules(" << vectorRules.size() << "):" << std::endl;
    Rule::ruleString(vectorRules);
    std::cout << "Queries(" << vectorQueries.size() << "):" << std::endl;
    Predicate::stringPredicate(vectorQueries, "Queries");
    std::cout << "Domain(" << domainSet.size() << "):" << std::endl;
    domainString();

}

void DatalogProgram::setDomain(std::vector<Parameter*> input) {
    for (auto & i : input) {
        domainSet.insert(i->paramString());
    }
}

void DatalogProgram::domainString() {
    for (const auto& elem : domainSet) {
        std::cout << "  " << elem << std::endl;
    }
}

DatalogProgram::DatalogProgram() = default;

DatalogProgram::~DatalogProgram()= default;
