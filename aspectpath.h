#ifndef ASPECTPATH_H
#define ASPECTPATH_H

#include "network.h"
#include <set>
#include <stack>

static class AspectPath {
    public:
        static void setNetwork(const Network &network, bool override = false);
        static std::vector<int>* getPath(std::string start, std::string end);
        static std::vector<int>* getPath(int start, int end);
        static std::vector<int>* traversePath(std::vector<int>* path, int start, int end);
    private:
        static inline bool initialized {false};
        static Network nodes;
};

#endif
