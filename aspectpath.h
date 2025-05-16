#ifndef ASPECTPATH_H
#define ASPECTPATH_H

#include "network.h"
#include <set>
#include <vector>
#include <string>

class AspectPath {
    public:
        AspectPath(const Network &network);
        std::vector<int>* getPath(std::string start, std::string end);
        std::vector<int>* getPath(int start, int end);
        //returns all nodes in fastest path
        std::set<int>* getInPath(const std::vector<int>* dij, int start, int end) const;
        std::vector<std::vector<int>*>* traversePath(const std::vector<int>* dij, int start, int end) const;
    private:
        void getInPath(const std::vector<int>* dij, int start, int end, std::set<int>* inPath) const;
        void traversePath(const std::vector<int>* dij, int start, int end, std::vector<std::vector<int>*>* paths, int count) const;
        Network nodes;
};

#endif
