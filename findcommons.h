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

//        void calculateCommons();
        void calculateDistances();
        enum tree {Herba,Metallum,Praecantatio};
        void oracle(std::string aspect, tree option);

        void addNode(std::string s);
        void clearNodes() {nodes.clear();}
        void clearHistory();

        void inputHistory(std::string path);
        void outputHistory(std::string path) const;
    private:
        Network network;
        AspectPath* aspectSearch;
        std::vector<int> nodes;
        std::vector<int> commons;
        std::map<std::pair<int,int>,std::vector<int>*> history;
};

#endif
