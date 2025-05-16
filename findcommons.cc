#ifndef FINDCOMMONS_CC
#define FINDCOMMONS_CC

#include "findcommons.h"

using namespace std;

FindCommons::FindCommons(const Network &nodes) {
    aspectSearch = new AspectPath(nodes);
    network = nodes;
}

FindCommons::~FindCommons() {
    clearHistory();
}

/*void FindCommons::calculateCommons() {
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
                        history[*query] = aspectSearch->getPath(query->first,query->second);
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
        vector<int>* path = aspectSearch->traversePath(dij, query->first, query->second);
        commons.push_back((*path)[path->size()/2]);
        delete path;
    }
    for (int i = 0; i<searches.size(); i++) {
        delete searches[i];
    }
}*/

void FindCommons::calculateDistances() {
    for (int i = 0; i<network.size(); i++) {
        for (int j = 0; j<network.size(); j++) {
            if (i!=j) {
                vector<int>* v = aspectSearch->getPath(j,i);
                pair<int,int> p(i,j);
                history[p] = aspectSearch->traversePath(v,j,i);
            }
        }
    }
}

void FindCommons::oracle(string aspect0, string aspect1) {
    int start = network.toInt(aspect0);
    int end = network.toInt(aspect1);
    pair<int,int> p(start,end);
    pair<int,int> rp(end,start);
    vector<int>* v;
    if (history.count(p)>0) {
        v = history[p];
    } else if (history.count(rp)>0) {
        v = history[rp];
    } else {
        v = aspectSearch->getPath(end,start);
        v = aspectSearch->traversePath(v, end,start);
    }
    cout << v->size() << endl;
    cout << p.first << ' ' << p.second << endl;
    for (int i = 0; i<v->size(); i++) {
        cout << network.toString((*v)[i]) << ' ';
    }
    cout << endl;
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
    ifstream read(path);
    int history_size;
    read >> history_size;
    for (int i = 0; i<history_size; i++) {
        string node0, node1;
        int count;
        read >> node0 >> node1 >> count;
        int n0Id = network.toInt(node0);
        int n1Id = network.toInt(node1);
        pair<int,int> p(n0Id,n1Id);
        vector<int>* v = new vector<int>;
        v->reserve(count);
        for (int j = 0; j<count; j++) {
            string node;
            read >> node;
            v->push_back(network.toInt(node));
        }
        history[p] = v;
    }
    read.close();
}

/*
file format (when something repeats twice and is followed by ... <> then it will repeat <> times in file)
:
history_size
nodeA0 nodeB0 count
link0 link1 ... <count>
nodeA1 nodeB1 count
link0 link1 ... <count>
... <history_size>
*/
void FindCommons::outputHistory(string path) const {
    ofstream write(path, ofstream::trunc);
    write << history.size() << endl;
    for (map<pair<int,int>,vector<int>*>::const_iterator i = history.cbegin(); i!=history.cend(); i++) {
        pair<int,int> query = i->first;
        vector<int> path = *history.at(query);
        string nodeA = network.toString(query.first);
        string nodeB = network.toString(query.second);
        write << nodeA << ' ' << nodeB << ' ' << path.size() << endl;
        for (int i = 0; i<path.size(); i++) {
            write << network.toString(path[i]);
            if (i<path.size()-1) {
                write << ' ';
            } else {
                write << endl;
            }
        }
    }
    write.close();
}

#endif
