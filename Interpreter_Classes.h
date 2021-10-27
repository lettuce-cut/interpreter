#ifndef PROJECT_2_INTERPRETER_CLASSES_H
#define PROJECT_2_INTERPRETER_CLASSES_H

#include "Lexer.h"
#include <set>
#include <map>

class Tuple {
private:
    std::vector<std::string> values;
public:
};

class Header {
private:
    std::vector<std::string> attributes;
public:
};

class Relation {
private:
    std::set<Tuple> relations;
public:
};

class Database {
private:
    std::map<std::string, Relation> database;
public:
};


#endif //PROJECT_2_INTERPRETER_CLASSES_H
