#include "Graph.h"


void Graph::evaluateSCC() {
//    std::cout << vectorSCC.size() << std::endl;
    for (long unsigned int i =0; i < vectorSCC.size(); i++) {
        std::string SSCline;
        long unsigned int counter = 0;
        for (long unsigned int j : vectorSCC[i]) {
            counter += 1;
            if (counter == vectorSCC[i].size() - 1) {
                SSCline += "R" + std::to_string(j) + ",";
            }
            else {
                SSCline += "R" + std::to_string(j);
            }
        }
        std::cout << "SCC: " << SSCline << std::endl;

        if ((vectorSCC[i].size() == 1) and (rulesFromParser[i].getHead().id != rulesFromParser[i].getBody()[0].id)) {
            for (long unsigned int R : vectorSCC[i]) {
                Rule::ruleString(rulesFromParser[R]);
                evaluateRule(rulesFromParser[R]).toString();
                std::cout << "1 passes: R" << R << std::endl;
            }
        }
        else {
            int preCount = 0;
            int postCount = -1;
            int passCount = 0;
            Relation evaluated = Relation();

            while (postCount != preCount) {
                long unsigned int allPass = rulesFromParser.size();
                for (long unsigned int k = i; k < rulesFromParser.size(); k++) {
                    preCount = myDatabase.database[rulesFromParser[k].getHead().id].relations.size();
                    evaluated = evaluateRule(rulesFromParser[k]);
                    postCount = myDatabase.database[rulesFromParser[k].getHead().id].relations.size();

                    if (preCount != postCount) {
                        Rule::ruleString(rulesFromParser[k]);
                        evaluated.toString();
                        allPass -= 1;
                    }
                    else {
                        Rule::ruleString(rulesFromParser[k]);
                    }
                    if (allPass != rulesFromParser.size()) {
                        postCount = preCount +1;
                    }
                }
                passCount += 1;
            }

            std::cout << passCount << " passes: " << SSCline << std::endl;
        }
    }
}

void Graph::reverseDepend() {

    for (long unsigned int i =0; i < rulesFromParser.size(); i++) {
        std::set<int> setAdd;
//        std::cout << "Looking at Rule #" << i << std::endl;
//        std::cout << "Head: " << rulesFromParser[i].getHead().id << std::endl;
        for (long unsigned int j = 0; j < rulesFromParser.size(); j++) {
//            std::cout << "Comparing with body of Rule#" << j << std::endl;
            for(long unsigned int k = 0; k < rulesFromParser[j].getBody().size(); k++) {
//                std::cout << "Checking against: " << rulesFromParser[j].getBody()[k].id << std::endl;
                if (rulesFromParser[i].getHead().id == rulesFromParser[j].getBody()[k].id) {
//                    std::cout << "MATCH" << std::endl;
                    setAdd.insert(j);
                    visited[i] = false;
                }
            }
        }
//        std::cout << std::endl;
        nodeListReverse.insert({i, setAdd});
    }
}

void Graph::forwardDepend() {

    for (long unsigned int i =0; i < rulesFromParser.size(); i++) {
        std::set<int> setAdd;
//        std::cout << "Looking at Rule #" << i << std::endl;
        for (long unsigned int j = 0; j <rulesFromParser[i].getBody().size(); j++) {
//            std::cout << "Looking at id: " << rulesFromParser[i].getBody()[j].id << std::endl;
            for (long unsigned int k = 0; k < rulesFromParser.size(); k++) {
//                std::cout << "Checking against Rule #id: " << rulesFromParser[k].getHead().id << std::endl;
                if (rulesFromParser[i].getBody()[j].id == rulesFromParser[k].getHead().id) {
//                    std::cout << "MATCH" <<std::endl;
                    setAdd.insert(k);
                    visited[i] = false;
                }
            }
        }
//        std::cout << std::endl;
        nodeListForward.insert({i, setAdd});
    }
//    std::cout << std::endl;
}

void Graph::printNodes() {
    for (long unsigned int i =0; i < rulesFromParser.size(); i++) {
        std::cout << "R" << i << ":";
        if (nodeListForward[i].size() != 0) {
            long unsigned int counter = 0;
            for (long unsigned int adjacent : nodeListForward[i]) {
                counter += 1;
                if (counter == nodeListForward[i].size()) {
                    std::cout << "R" << adjacent;
                }
                else {
                    std::cout << "R" << adjacent << ",";
                }
            }
            std::cout << std::endl;
        }
        else {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

void Graph::dfsReverse(int currNode) {
//    std::cout << "TREE" << std::endl;
    visited[currNode] = true;
//    std::cout << currNode << " marked as true" << std::endl;
    for (long unsigned int adjacent: nodeListReverse[currNode]) {
//        std::cout << "Checking if adjacent " << adjacent << " is false" << std::endl;
        if (visited[adjacent] == false) {
//            std::cout << adjacent << " is false" << std::endl;
            dfsReverse(adjacent);
        }
    }
//    std::cout << currNode << " being added to postorder" << std::endl;
    postOnReverse.push_back(currNode);
}

void Graph::dfsForward(int currNode) {
    //    std::cout << "TREE" << std::endl;
    visited[currNode] = true;
//    std::cout << currNode << " marked as true" << std::endl;
    for (long unsigned int adjacent: nodeListForward[currNode]) {
//        std::cout << "Checking if adjacent " << adjacent << " is false" << std::endl;
        if (visited[adjacent] == false) {
//            std::cout << adjacent << " is false" << std::endl;
            dfsForward(adjacent);
        }
    }
    postOnForward.push_back(currNode);
//    std::cout << currNode << " being added to SCC" << std::endl;
    SCC.insert(currNode);
}

void Graph::forestReverse() {
//    std::cout << "REVERSE FOREST" << std::endl;
    postOnReverse.clear();
    for (auto &it : visited) {
        it.second = false;
    }
    for (auto &it : nodeListReverse) {
//        std::cout << "CurrNode = " << it.first << std::endl;
        if (visited[it.first] == false) {
            dfsReverse(it.first);
        }
    }
//    printPost();
}

void Graph::forestForward() {
//    std::cout << "FORWARD" << std::endl;
    for (auto &it : visited) {
        it.second = false;
    }
    for (long int i = postOnReverse.size()-1; i >-1; i--) {
//        std::cout << "Curr Node: " << postOnReverse[i] << std::endl;
        if (visited[postOnReverse[i]] == false) {
            dfsForward(postOnReverse[i]);

            vectorSCC.push_back(SCC);
            SCC.clear();
        }
    }
//    printPost();
}

void Graph::printPost() {
    for (long unsigned int i =0; i < postOnReverse.size(); i++) {
        std::cout << postOnReverse[i] << " + ";
    }
    std::cout << std::endl;
}

Graph::Graph(DatalogProgram fromParser) {
    schemesFromParser = fromParser.getSchemes();
    factsFromParser = fromParser.getFacts();
    queriesFromParser = fromParser.getQueries();
    rulesFromParser = fromParser.getRules();
}

Graph::~Graph() {
}


//From Interpreter
void Graph::makeRelation() {
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

Relation Graph::evaluatePredicate(Predicate p) {
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

void Graph::evaluateAll() {
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

Relation Graph::evaluateRule(Rule r) {
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
//            std::cout << "WON'T JOIN" << std::endl;
            ogReturn = toReturn;
        }
        else {
//            std::cout << "WILL JOIN" << std::endl;
            ogReturn = toReturn.Join(ogReturn);
        }
    }

//    std::cout << std::endl;
//    std::cout << "TEST" << std::endl;
//    ogReturn.toString();
//    std::cout << std::endl;

    //STEP 3
    std::vector<int> indices;
    std::vector<std::string> forNames;

    std::vector<std::string> toCompare;
    for (long unsigned int i =0; i < r.getHead().parameters.size(); i++) {
        toCompare.push_back(r.getHead().parameters[i]->paramString());
    }

    if (toCompare == ogReturn.relationHeader.attributes) {
        for (long unsigned int i =0; i < r.getHead().parameters.size(); i++) {
            indices.push_back(i);
        }
    }

    else {
        for (long unsigned int i =0; i < r.getHead().parameters.size(); i++) {
            for(long unsigned int j=0; j< ogReturn.relationHeader.attributes.size(); j++) {
                if (r.getHead().parameters[i]->paramString() == ogReturn.relationHeader.attributes[j]) {
                    indices.push_back(j);
                }
            }
        }
    }
    ogReturn = ogReturn.Project(indices);
//    ogReturn.relationHeader.toString();

//    STEP 4
    for (long unsigned int i =0; i < myDatabase.database[r.getHead().id].relationHeader.attributes.size(); i++) {
        forNames.push_back(myDatabase.database[r.getHead().id].relationHeader.attributes[i]);
    }
    ogReturn = ogReturn.Rename(forNames);
//    ogReturn.relationHeader.toString();

    //Step 5
    Relation relationsAdded = Relation();
    myDatabase.database[r.getHead().id].relations = ogReturn.Uniter(myDatabase.database[r.getHead().id], relationsAdded.relations).relations;
    ogReturn.relations = relationsAdded.relations;
//    ogReturn.toString();
    return ogReturn;
}



