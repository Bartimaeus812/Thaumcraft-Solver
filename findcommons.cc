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

void FindCommons::calculateCommons() {
    commons.clear();
    set<int> uniques;
    for (int i = 0; i<nodes.size(); i++) {
        for (int j = i+1; j<nodes.size(); j++) {
            pair<int,int> p(i,j);
            set<int> s = *history[p];
            for (set<int>::const_iterator k = s.cbegin(); k!=s.cend(); k++) {
                int kk = *k;
                if (uniques.count(kk)>0||nodes.size()==2) {
                    commons.push_back(kk);
                } else {
                    uniques.insert(kk);
                }
            }
        }
    }
}

void FindCommons::calculateDistances() {
    for (int i = 0; i<network.size(); i++) {
        for (int j = 0; j<network.size(); j++) {
            if (i!=j) {
                vector<int>* v = aspectSearch->getPath(j,i);
                pair<int,int> p(i,j);
                history[p] = aspectSearch->getInPath(v,j,i);
                delete[] v;
            }
        }
    }
}

void FindCommons::displayCommons() {
    for (int i = 0; i<commons.size(); i++) {
        cout << network.toString(commons[i]) << ' ';
    }
    cout << endl;
}

void FindCommons::oracle(string nodeA, string nodeB) {
    int nA = network.toInt(nodeA);
    int nB = network.toInt(nodeB);
    vector<int>* v = aspectSearch->getPath(nB,nA);
    vector<vector<int>*>* vv = aspectSearch->traversePath(v, nB, nA);
    for (int i = 0; i<vv->size(); i++) {
        vector<int>* path = vv->at(i);
        cout << i << ':';
        for (int j = 0; j<path->size(); j++) {
            string node = network.toString(path->at(j));
            cout << node << ' ';
        }
        cout << endl;
        delete path;
    }
    delete[] v;
    delete vv;
}

void FindCommons::clearHistory() {
    for (map<pair<int,int>,set<int>*>::iterator i = history.begin(); i!=history.end(); i++) {
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
        set<int>* s = new set<int>;
        for (int j = 0; j<count; j++) {
            string node;
            read >> node;
            s->insert(network.toInt(node));
        }
        history[p] = s;
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
    for (map<pair<int,int>,set<int>*>::const_iterator i = history.cbegin(); i!=history.cend(); i++) {
        pair<int,int> query = i->first;
        set<int> path = *history.at(query);
        string nodeA = network.toString(query.first);
        string nodeB = network.toString(query.second);
        write << nodeA << ' ' << nodeB << ' ' << path.size() << endl;
        int j = 0;
        for (set<int>::iterator jit = path.begin(); jit!=path.end(); jit++) {
            write << network.toString(*jit);
            if (j<path.size()-1) {
                write << ' ';
            } else {
                write << endl;
            }
            j++;
        }
    }
    write.close();
}

#endif
