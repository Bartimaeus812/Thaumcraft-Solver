#ifndef ASPECTPATH_CC
#define ASPECTPATH_CC

#include "aspectpath.h"

using namespace std;

AspectPath::AspectPath(const Network &network) {
    nodes = network;
}

void AspectPath::calculate(string start, string end) {
    int sid = nodes.toInt(start);
    int eid = nodes.toInt(end);
    //dij algorithm
    vector<int> unvisited;
    set<int> visited;
    int* times = new int[nodes.size()];
    vector<int>* previous = new vector<int>[nodes.size()];
    //populate unvisited and times
    for (int i = 0; i<nodes.size(); i++) {
        if (i!=eid) {
            unvisited.push_back(i);
        }
        times[i] = INT_MAX;
    }
    times[sid] = 0;
    //view all nodes
    while (unvisited.size()>0) {
        //get min time node
        int minTime = INT_MAX;
        int minNode = -1;
        vector<int>::iterator minIter;
        for (vector<int>::iterator i = unvisited.begin(); i!=unvisited.end(); i++) {
            int n = *i;
            int t = times[n];
            if (t<minTime) {
                minTime = t;
                minNode = n;
                minIter = i;
            }
        }
        //remove node from search
        unvisited.erase(minIter);
        //apply travel time to connections
        vector<int> connections = nodes[minNode];
        for (int i = 0; i<connections.size(); i++) {
            int n = connections[i];
            //travel time is 1
            if (minTime+1<=times[n]) {
                times[n] = minTime+1;
                //nodes with equal travel time also previous
                previous[n].push_back(minNode);
            }
        }
    }
    delete[] times;
    for (int i = 0; i<nodes.size(); i++) {
        dij = previous;
    }
}

#endif
