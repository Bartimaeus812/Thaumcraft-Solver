#ifndef FINDCOMMONS_CC
#define FINDCOMMONS_CC

#include "findcommons.h"

using namespace std;

FindCommons::FindCommons(const Network &nodes) {
    AspectPath::setNetwork(nodes);
    network = nodes;
}

FindCommons::~FindCommons() {
    clearHistory();
}

void FindCommons::calculateCommons() {
    vector<pair<int,int>*> searches;
    //search between all nodes
    for (int i = 0; i<nodes.size(); i++) {
        for (int j = 0; j<nodes.size(); j++) {
            if (i!=j && nodes[i]!=nodes[j]) {
                pair<int,int>* query = new pair<int,int>(nodes[i],nodes[j]);
                //check if query in history else
                //invert query order
                //check if query in history else
                //invert query order
                //add new search to history
                if (history.count(*query)>0) {
                    searches.push_back(query);
                } else {
                    swap(query->first, query->second);
                    if (history.count(*query)>0) {
                        searches.push_back(query);
                    } else {
                        swap(query->first, query->second);
                        history[*query] = AspectPath::getPath(query->first,query->second);
                        searches.push_back(query);
                    }
                }
            }
        }
    }
    //if single search, add center node of search to common nodes
    if (searches.size()==1) {
        pair<int,int>* query = searches[0];
        vector<int>* dij = history[*query];
        vector<int>* path = AspectPath::traversePath(dij, query->first, query->second);
        commons.push_back((*path)[path->size()/2]);
        delete path;
    }
    for (int i = 0; i<searches.size(); i++) {
        delete searches[i];
    }
}

void FindCommons::addNode(string s) {
    nodes.push_back(network.toInt(s));
}

void FindCommons::clearHistory() {
    for (map<pair<int,int>,vector<int>*>::iterator i = history.begin(); i!=history.end(); i++) {
        delete i->second;
    }
    history.clear();
}

void FindCommons::inputHistory(string path) {

}

/*
file format (when something repeats twice and is followed by ... <> then it will repeat <> times in file)
:
history_size dij_size
nodeA0 nodeB0
node0 node0_count
0link0 0link1 ... <node0_count>
node1 node1_count
1link0 1link1 ... <node1_count>
... <dij_size>
nodeA1 nodeB1
node0 node0_count
0link0 0link1 ... <node0_count>
node1 node1_count
1link0 1link1 ... <node1_count>
... <dij_size>
... <history_size>
*/
void FindCommons::outputHistory(string path) const {
    ofstream write(path);
    write << history.size() << ' ' << nodes.size() << endl;
    for (map<pair<int,int>,vector<int>*>::const_iterator i = history.cbegin(); i!=history.cend(); i++) {
        pair<int,int> query = i->first;
        vector<int>* dij = history.at(query);
        string nodeA = network.toString(query.first);
        string nodeB = network.toString(query.second);
        write << nodeA << ' ' << nodeB << endl;
        for (int i = 0; i<nodes.size(); i++) {
            string node = network.toString(i);
            int count = dij[i].size();
            write << node << ' ' << count << endl;
            for (int j = 0; j<count; j++) {
                write << network.toString(dij[i][j]);
                if (j<count-1) {
                    write << ' ';
                } else {
                    write << '\n';
                }
            }
        }
    }
}

#endif
