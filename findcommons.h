#ifndef FINDCOMMONS_H
#define FINDCOMMONS_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

class FindCommons {
    public:
        FindCommons(std::map<std::string,std::pair<std::string,std::string>*> nodeMap);
        void calculateCommons();

        void addNode(std::string s);
        void clearNodes() {nodes.clear();}
    private:
        std::map<std::string,std::pair<std::string,std::string>*> network;
        std::vector<int> nodes;
        std::vector<int> commons;
};

#endif
