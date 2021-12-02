#include "Interpreter.h"
#include "Relation.h"

Interpreter::Interpreter(DatalogProgram fromParser) {
    schemesFromParser = fromParser.getSchemes();
    factsFromParser = fromParser.getFacts();
    queriesFromParser = fromParser.getQueries();
    rulesFromParser = fromParser.getRules();
}

void Interpreter::makeRelation() {
    for (long unsigned int i = 0; i < schemesFromParser.size(); i++) {
        Relation toDatabase = Relation(schemesFromParser[i].id, Header(schemesFromParser[i].parameters));
        for (long unsigned int j = 0; j < factsFromParser.size(); j++) {
            if (factsFromParser[j].id == schemesFromParser[i].id) {
                toDatabase.addTuple(factsFromParser[j].parameters);
            }
        }
        myDatabase.addRelation(toDatabase);
    }
}

Relation Interpreter::evaluatePredicate(Predicate p) {
    Relation toReturn = myDatabase.database[p.id];
    std::vector<int> indices;
    std::map<int, std::string> position;
    std::vector<std::string> forNames;


    for (long unsigned int i = 0; i < p.parameters.size(); i++) {
        int count = 0;
        if (p.parameters[i]->isConstant == true) {
            toReturn = toReturn.SelectOne(i, p.parameters[i]->paramString());
        }
        else {//is a variable
            if (position.find(i)->first == 0) {
                position[i] = p.parameters[i]->paramString();
                count += 1;
            }
            else {
                for (long unsigned int m = 0; m < position.size(); m++) {
                    if ((i != m) and (p.parameters[i]->paramString() == position[m])) {
                        toReturn = toReturn.SelectTwo(i, m);
                    }
                    else{
                        position[i] = p.parameters[i]->paramString();
                        count += 1;
                    }
                }
            }
            if (count > 0) {
                indices.push_back(i);
            }
        }
    }
    toReturn = toReturn.Project(indices);
    for (int index : indices) {
        if (forNames.size() == 0) {
            forNames.push_back(position[index]);
        }
        else {
            int count = 0;
            for (std::string name : forNames) {
                if (name == position[index]) {
                    count += 1;
                }
            }
            if (count == 0 and position[index] != "") {
                forNames.push_back(position[index]);
            }
        }
    }
    toReturn = toReturn.Rename(forNames);
    return toReturn;
}

void Interpreter::evaluateAll() {
    std::cout << "Query Evaluation" << std::endl;
    for (long unsigned int i = 0; i < queriesFromParser.size(); i++) {
        Relation evaluated = evaluatePredicate(queriesFromParser[i]);
        std::cout << queriesFromParser[i].id << "(";
        for (long unsigned int j =0; j < queriesFromParser[i].parameters.size(); j++) {
            if (j == queriesFromParser[i].parameters.size() -1) {
                std::cout << queriesFromParser[i].parameters[j]->paramString() << ")?";
            }
            else {
                std::cout << queriesFromParser[i].parameters[j]->paramString() << ",";
            }
        }
        if (evaluated.relations.size() == 0) {
            std::cout << "No" << std::endl;
        }
        else {
            std::cout << " Yes(" << evaluated.relations.size() << ")" << std::endl;
            evaluated.toString();
        }
    }
}

Relation Interpreter::evaluateRule(Rule r) {
    Relation ogReturn = Relation();
    //STEPS 1 AND 2
//    std::cout << "TEST" <<std::endl;
    for (long unsigned int s =  0; s < r.getBody().size(); s++) {
        Relation toReturn = myDatabase.database[r.getBody().at(s).id];

//        std::cout << "TEST" <<std::endl;
//        std::cout << toReturn.relationName << std::endl;
//        toReturn.toString();
//        std::cout << "HEADER TEST" << std::endl;
//        toReturn.relationHeader.toString();

        std::vector<int> indices;
        std::map<int, std::string> position;
        std::vector<std::string> forNames;

        for (long unsigned int i = 0; i < r.getBody().at(s).parameters.size(); i++) {
            int count = 0;
            if (r.getBody().at(s).parameters[i]->isConstant == true) {
                toReturn = toReturn.SelectOne(i, r.getBody().at(s).parameters[i]->paramString());
            }
            else {//is a variable
                if (position.find(i)->first == 0) {
                    position[i] = r.getBody().at(s).parameters[i]->paramString();
                    count += 1;
                }
                else {
                    for (long unsigned int L = 0; L < position.size(); L++) {
                        if ((i != s) and (r.getBody().at(s).parameters[i]->paramString() == position[L])) {
                            toReturn = toReturn.SelectTwo(i, L);
                        }
                        else{
                            position[i] = r.getBody().at(s).parameters[i]->paramString();
                            count += 1;
                        }
                    }
                }
                if (count > 0) {
                    indices.push_back(i);
                }
            }
        }

        toReturn = toReturn.Project(indices);
//        std::cout << "TEst" <<std::endl;
//        toReturn.toString();

        for (int index : indices) {
            if (forNames.size() == 0) {
                forNames.push_back(position[index]);
            }
            else {
                int count = 0;
                for (std::string name : forNames) {
                    if (name == position[index]) {
                        count += 1;
                    }
                }
                if (count == 0 and position[index] != "") {
                    forNames.push_back(position[index]);
                }
            }
        }
        toReturn = toReturn.Rename(forNames);
//        std::cout << "Test" <<std::endl;
//        toReturn.toString();


        if (ogReturn.relations.size() == 0) {
            ogReturn = toReturn;
//            std::cout << "ascofialaje" <<std::endl;
//            ogReturn.toString();
        }
        else {
            ogReturn = toReturn.Join(ogReturn);
        }
    }

    //STEP 3
    std::vector<int> indices;
    std::vector<std::string> forNames;

    for (long unsigned int i =0; i < r.getHead().parameters.size(); i++) {
        for(long unsigned int j=0; j< ogReturn.relationHeader.attributes.size(); j++) {
            if (r.getHead().parameters[i]->paramString() == ogReturn.relationHeader.attributes[j]) {
                indices.push_back(j);
            }
        }
    }
    ogReturn = ogReturn.Project(indices);


//    STEP 4
    for (long unsigned int i =0; i < myDatabase.database[r.getHead().id].relationHeader.attributes.size(); i++) {
        forNames.push_back(myDatabase.database[r.getHead().id].relationHeader.attributes[i]);
    }
    ogReturn = ogReturn.Rename(forNames);

    //Step 5
    myDatabase.database[r.getHead().id].relations = ogReturn.Uniter(myDatabase.database[r.getHead().id]).relations;
//    std::cout << "FINAL" << std::endl;
    return ogReturn;
}

void Interpreter::allRules() {
    int preCount = 0;
    int postCount = -1;
    int passCount = 0;


    while (postCount != preCount) {
        long unsigned int allPass = rulesFromParser.size();
        for (long unsigned int i = 0; i < rulesFromParser.size(); i++) {
            preCount = myDatabase.database[rulesFromParser[i].getHead().id].relations.size();
            evaluateRule(rulesFromParser[i]);
//            Rule::ruleString(rulesFromParser[i]);
//            evaluateRule(rulesFromParser[i]).toString();
            postCount = myDatabase.database[rulesFromParser[i].getHead().id].relations.size();
//            std::cout << preCount << " + " << postCount << std::endl;

            if (preCount != postCount) {
                Rule::ruleString(rulesFromParser[i]);
                evaluateRule(rulesFromParser[i]).toString();
                allPass -= 1;
            }
            else {
                Rule::ruleString(rulesFromParser[i]);
            }
            if (allPass != rulesFromParser.size()) {
                postCount = preCount +1;
            }
//            std::cout << preCount << " + " << postCount << std::endl;
        }
        passCount += 1;
    }


    std::cout << "\nSchemes populated after " << passCount << " passes through the Rules.\n" << std::endl;
}

Interpreter::~Interpreter() = default;
