#ifndef FINDCOMMONS_H
#define FINDCOMMONS_H

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "aspectpath.h"
#include <fstream>

class FindCommons {
    public:
        FindCommons(const Network &nodes);
        ~FindCommons();

        void calculateCommons();
        //calculate nodes in fastest path for all nodes to all nodes
        void calculateDistances();

        void displayCommons();

        void oracle(std::string nodeA, std::string nodeB);

        //add node to find common for
        void addNode(std::string s) {nodes.push_back(network.toInt(s));}
        void clearNodes() {nodes.clear();}
        void clearHistory();

        void inputHistory(std::string path);
        void outputHistory(std::string path) const;
    private:
        Network network;
        AspectPath* aspectSearch;
        std::vector<int> nodes;
        std::vector<int> commons;
        std::map<std::pair<int,int>,std::set<int>*> history;
};

#endif
