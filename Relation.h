#ifndef PROJECT_2_RELATION_H
#define PROJECT_2_RELATION_H

#include <set>
#include "Header.h"
#include "Tuple.h"
#include <list>

class Relation {
private:
public:
    Relation();

    std::string relationName;
    std::set<Tuple> relations;
    Header relationHeader;

    Relation(std::string name, Header header);
    ~Relation();

    Relation SelectOne(int index, std::string value);
    Relation SelectTwo(int index, int indexTwo);
    Relation Project(std::vector<int> forProject);
    Relation Rename(std::vector<std::string> forRename);
    void addTuple(Tuple toAdd);
    void toString();
};

#endif //PROJECT_2_RELATION_H
