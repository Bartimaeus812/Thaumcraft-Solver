#ifndef ASPECTPATH_H
#define ASPECTPATH_H

#include "network.h"
#include <set>
#include <stack>

class AspectPath {
    public:
        AspectPath(const Network &network);
        std::vector<int>* getPath(std::string start, std::string end);
        std::vector<int>* getPath(int start, int end);
        //reverses path
        std::vector<int>* traversePath(const std::vector<int>* path, int start, int end);
    private:
        Network nodes;
};

#endif
