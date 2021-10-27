#ifndef PROJECT_2_RELATION_H
#define PROJECT_2_RELATION_H

#include <set>
#include "Header.h"
#include "Tuple.h"
#include <list>

class Relation {
private:
    std::set<Tuple> relations;
    std::string relationName;
    Header* relationHeader;
public:
    Relation();
    ~Relation();
    Relation SelectOne(int index, std::string value);
    Relation SelectTwo(int index, int indexTwo);
    Relation Project(std::list<int> forProject);
    Relation Rename(std::list<std::string> forRename);
};

#endif //PROJECT_2_RELATION_H
