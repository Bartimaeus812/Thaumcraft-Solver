#ifndef ASPECTPATH_H
#define ASPECTPATH_H

#include "network.h"
#include <set>
#include <stack>

class AspectPath {
    public:
        AspectPath(const Network &network);
        void calculate(std::string start, std::string end);
        std::vector<std::string>* getPaths(int n) const;
    private:
        Network nodes;
        std::vector<int>* dij;
};

#endif
