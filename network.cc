#ifndef NETWORK_CC
#define NETWORK_CC

#include "network.h"

using namespace std;

Network::Network(map<string,pair<string,string>> nodes) {
    idCount = 0;
    idTable[""] = -1;
    ridTable[-1] = "";
    _size = nodes.size();
    data = new vector<int>[_size];
    for (map<string,pair<string,string>>::const_iterator i = nodes.cbegin(); i!=nodes.cend(); i++) {
        string node0 = i->first;
        pair<string,string> parents = nodes.at(node0);
        string node1 = parents.first;
        string node2 = parents.second;
        int nid0 = addId(node0);
        int nid1 = addId(node1);
        int nid2 = addId(node2);
        if (nid1>-1) {
            data[nid0].push_back(nid1);
            data[nid0].push_back(nid2);
            data[nid1].push_back(nid0);
            data[nid2].push_back(nid0);
        }
    }
}

vector<int> Network::operator[](int i) const {
    return data[i];
}

int Network::addId(string s) {
    if (idTable.count(s)==0) {
        idTable[s] = idCount;
        ridTable[idCount++] = s;
    }
    return idTable[s];
}

int Network::toInt(string s) const {
    if (idTable.count(s)==0) {
        throw AspectSpelling();
    }
    return idTable.at(s);
}

#endif
