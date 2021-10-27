#ifndef PROJECT_2_DATALOGPROGRAM_H
#define PROJECT_2_DATALOGPROGRAM_H

#include <vector>
#include <iostream>
#include "Lexer.h"
#include "Rule.h"
#include <set>
class DatalogProgram {
private:
    int index = 0;
    void datalogProgramParse(std::vector<Token *> toParse);
    void schemeListPars(const std::vector<Token *> &toParse);
    void factListParse(const std::vector<Token *> &toParse);
    void ruleListParse(const std::vector<Token *> &toParse);
    void queryListParse(const std::vector<Token *> &toParse);
    void schemeParse(std::vector<Token *> toParse);
    void factParse(std::vector<Token *> toParse);
    void ruleParse(std::vector<Token *> toParse);
    void queryParse(std::vector<Token *> toParse);
    void headPredicateParse(std::vector<Token *> toParse);
    void predicateParse(std::vector<Token *> toParse);
    void predicateListParse(std::vector<Token *> toParse);
    void parameterList(std::vector<Token *> toParse);
    void stringList(std::vector<Token *> toParse);
    void idListParse(std::vector<Token *> toParse);
    void parameterParse(std::vector<Token *> toParse);
    void Match(Token *pToken, TokenType);
public:
    DatalogProgram();
    ~DatalogProgram();
    void parseRun(const std::vector<Token *> &toParse);

    void outputString();
    void setDomain(std::vector<Parameter *> input);
    void domainString();
    std::set<std::string> domainSet;

    void predicateParseRules(std::vector<Token *> toParse);
};
#endif //PROJECT_2_DATALOGPROGRAM_H
