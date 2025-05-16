#ifndef ASPECTPATH_CC
#define ASPECTPATH_CC

#include "aspectpath.h"

using namespace std;

AspectPath::AspectPath(const Network &network) {
    nodes = network;
}

vector<int>* AspectPath::getPath(string start, string end) {
    int sid = nodes.toInt(start);
    int eid = nodes.toInt(end);
    return getPath(sid, eid);
}

vector<int>* AspectPath::getPath(int sid, int eid) {
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
    return previous;
}

set<int>* AspectPath::getInPath(const vector<int>* dij, int start, int end) const {
    set<int>* inPath = new set<int>;
    getInPath(dij,start,end,inPath);
    return inPath;
}

void AspectPath::getInPath(const vector<int>* dij, int start, int end, set<int>* inPath) const {
    inPath->insert(end);
    if (end==start) {
        return;
    }
    for (int i = 0; i<dij[end].size(); i++) {
        getInPath(dij,start,dij[end][i],inPath);
    }
}

vector<vector<int>*>* AspectPath::traversePath(const vector<int>* dij, int start, int end) const {
    vector<vector<int>*>* paths = new vector<vector<int>*>;
    paths->push_back(new vector<int>);
    traversePath(dij, start, end, paths, 0);
    return paths;
}

void AspectPath::traversePath(const vector<int>* dij, int start, int end, vector<vector<int>*>* paths, int count) const {
    paths->at(count)->push_back(end);
    int originNum = paths->at(count)->size();
    if (end==start) {
        return;
    }
    for (int i = 0; i<dij[end].size(); i++) {
        if (i>0) {
            paths->push_back(new vector<int>);
            for (int j = 0; j<originNum; j++) {
                paths->at(paths->size()-1)->push_back(paths->at(count)->at(j));
            }
        }
        traversePath(dij, start, dij[end][i], paths, paths->size()-1);
    }
}

#endif
