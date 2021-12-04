#include "Interpreter.h"
#include "Relation.h"

Interpreter::Interpreter(DatalogProgram fromParser) {
    schemesFromParser = fromParser.getSchemes();
    factsFromParser = fromParser.getFacts();
    queriesFromParser = fromParser.getQueries();
    rulesFromParser = fromParser.getRules();
}

void Interpreter::makeRelation() {
    for (auto & i : schemesFromParser) {
        Relation toDatabase = Relation(i.id, Header(i.parameters));
        for (auto & j : factsFromParser) {
            if (j.id == i.id) {
                toDatabase.addTuple(j.parameters);
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
        if (p.parameters[i]->isConstant) {
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
        if (forNames.empty()) {
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
    for (auto & i : queriesFromParser) {
        Relation evaluated = evaluatePredicate(i);
        std::cout << i.id << "(";
        for (long unsigned int j =0; j < i.parameters.size(); j++) {
            if (j == i.parameters.size() -1) {
                std::cout << i.parameters[j]->paramString() << ")?";
            }
            else {
                std::cout << i.parameters[j]->paramString() << ",";
            }
        }
        if (evaluated.relations.empty()) {
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
//        std::cout << "TEST + " << s << std::endl;
//        ogReturn.toString();
//        std::cout << std::endl;

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
            if (r.getBody().at(s).parameters[i]->isConstant) {
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
            if (forNames.empty()) {
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


        if (ogReturn.relations.empty()) {
//            std::cout << "WON'T JOIN" << std::endl;
            ogReturn = toReturn;
        }
        else {
//            std::cout << "WILL JOIN" << std::endl;
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
    Relation relationsAdded = Relation();
    myDatabase.database[r.getHead().id].relations = ogReturn.Uniter(myDatabase.database[r.getHead().id], relationsAdded.relations).relations;
    ogReturn.relations = relationsAdded.relations;
//    ogReturn.toString();
    return ogReturn;
}

void Interpreter::allRules() {
    int preCount = 0;
    int postCount = -1;
    int passCount = 0;
    Relation evaluated = Relation();


    while (postCount != preCount) {
        long unsigned int allPass = rulesFromParser.size();
        for (auto & i : rulesFromParser) {
            preCount = myDatabase.database[i.getHead().id].relations.size();
//            std::cout << "RULE #" << i<< std::endl;
            evaluated = evaluateRule(i);
//            Rule::ruleString(rulesFromParser[i]);
//            evaluateRule(rulesFromParser[i]).toString();
            postCount = myDatabase.database[i.getHead().id].relations.size();
//            std::cout << preCount << " + " << postCount << std::endl;

            if (preCount != postCount) {
                Rule::ruleString(i);
                evaluated.toString();
                allPass -= 1;
            }
            else {
                Rule::ruleString(i);
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
