#ifndef PROJECT_2_GRAPH_H
#define PROJECT_2_GRAPH_H

#include <map>
#include <set>
#include "Lexer.h"
#include "DatalogProgram.h"
#include "Database.h"
class Graph
{
private:
    std::vector<Predicate> schemesFromParser;
    std::vector<Predicate> factsFromParser;
    std::vector<Predicate> queriesFromParser;
    std::vector<Rule> rulesFromParser;
    std::map<int, std::set<int> > nodeListForward;
    std::map<int, std::set<int> > nodeListReverse;
    std::vector<int> postOnReverse;
    std::vector<int> postOnForward;
    std::map<int, bool> visited;
    std::set<int> SCC;
    std::vector<std::set<int>> vectorSCC;
public:
    Graph(DatalogProgram fromParser);
    ~Graph();

    void printNodes();
    void forwardDepend();
    void reverseDepend();

    void dfsReverse(int currNode);
    void dfsForward(int currNode);
    void forestReverse();
    void forestForward();
    void printPost();

    void evaluateSCC();



    //From Interpreter
    Database myDatabase;
    void makeRelation();
    Relation evaluatePredicate(Predicate p);
    void evaluateAll();
    Relation evaluateRule(Rule r);
};


#endif //PROJECT_2_GRAPH_H
