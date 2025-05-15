#ifndef OBSIDIAN_CC
#define OBSIDIAN_CC

#include "obsidian.h"

using namespace std;

Obsidian::Obsidian(string path, bool isFileNotFolder) {
    if (isFileNotFolder) {
        int n;
        ifstream reader(path);
        reader >> n;
        string s;
        getline(reader, s);
        for (int i = 0; i<n; i++) {
            string node0,node1,node2;
            reader >> node0 >> node1 >> node2;
            if (node1=="Primal") {
                node1 = "";
                node2 = "";
            }
            nodes[node0] = new pair<string,string>(node1,node2);
        }
        for (int i = 0; i<n; i++) {
            string node;
            int count,maxCount;
            reader >> node >> count >> maxCount;
            nodeInfo* info = new nodeInfo;
            info->count = count;
            info->maxCount = maxCount;
            nodeData[node] = info;
        }
    } else {
        for (const auto & entry : filesystem::directory_iterator(path)) {
            string node0 = entry.path().filename().string();
            int pos = node0.find(".md");
            if (pos>=0) {
                node0 = node0.substr(0,pos);
                ifstream reader(entry.path());
                string s, node1, node2;
                
                getline(reader, s);
                if (s.length()==0) {
                    node1 = "";
                    node2 = "";
                } else {
                    pos = s.find(']')-2;
                    node1 = s.substr(2,pos);
                    s = s.substr(pos+4);
                    pos = s.length()-2;
                    node2 = s.substr(0,pos);
                }

                nodes[node0] = new pair<string,string>(node1,node2);
                cout << node0 << " = " << node1 << " + " << node2 << endl;
            }
        }
    }
}

void Obsidian::inputCounts() {
    for (map<string,pair<string,string>*>::iterator i = nodes.begin(); i!=nodes.end(); i++) {
        string node = i->first;
        cout << "Count of " << node << ": ";
        cin >> nodeData[node]->count;
    }
}

void Obsidian::calculateMaxCounts() {
    map<string,int> depths;
    for (map<string,pair<string,string>*>::iterator i = nodes.begin(); i!=nodes.end(); i++) {
        string node = i->first;
        depths[node] = getDepth(node);
    }
    sort(depths.begin(),depths.end(),[](const pair<string,int> &a, const pair<string,int> &b) {
        return a.second < b.second;
    });
    for (map<string,int>::iterator i = depths.begin(); i!=depths.end(); i++) {
        string node = i->first;
        if (i->second==0) {
            nodeData[node]->maxCount = nodeData[node]->count;
        } else {
            pair<string,string> parents = *nodes[node];
            nodeData[node]->maxCount = min(nodeData[parents.first]->maxCount, nodeData[parents.second]->maxCount);
        }
    }
}

/*
file format (when something repeats twice and is followed by ... <> then it will repeat <> times in file)
:
nodes_size
node00 node10 node20
node01 node11 node21
... <nodes_size>
node0 count0 potential_count0
node1 count1 potential_count1
... <nodes_size>
*/
void Obsidian::FileOutput(string path) const {
    ofstream write(path, ofstream::trunc);
    write << nodes.size() << endl;
    for (map<string,pair<string,string>*>::const_iterator i = nodes.cbegin(); i!=nodes.cend(); i++) {
        string node0 = i->first;
        const pair<string,string> parents = *nodes.at(node0);
        string node1 = parents.first;
        string node2 = parents.second;
        if (node1=="") {
            node1 = "Primal";
            node2 = "Aspect";
        }
        write << node0 << ' ' << node1 << ' ' << node2 << endl;
    }
    for (map<string,nodeInfo*>::const_iterator i = nodeData.cbegin(); i!=nodeData.cend(); i++) {
        string node = i->first;
        const nodeInfo info = *nodeData.at(node);
        int count = info.count;
        int maxCount = info.maxCount;
        write << node << ' ' << count << ' ' << maxCount << endl;
    }
}

int Obsidian::getDepth(string s) const {
    pair<string,string> parents = *nodes.at(s);
    if (parents.first=="") {
        return 0;
    } else {
        return 1+min(getDepth(parents.first), getDepth(parents.second));
    }
}

const map<string,pair<string,string>*> Obsidian::GetNodes() const {
    return nodes;
}

const map<string,Obsidian::nodeInfo*> Obsidian::GetData() const {
    return nodeData;
}

#endif
