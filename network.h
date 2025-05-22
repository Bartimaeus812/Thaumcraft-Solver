#ifndef NETWORK_H
#define NETWORK_H

#include <map>
#include <string>
#include <vector>
#include "AspectSpelling.h"
#include "obsidian.h"

class Network {
    public:
        Network() {}
        Network(const std::map<std::string,std::pair<std::string,std::string>> nodes);
        
        std::vector<int> operator[](int i) const;

        int toInt(std::string s) const;
        std::string toString(int i) const {return ridTable.at(i);}
        size_t size() const {return _size;}
    private:
        int addId(std::string s);
        size_t _size;
        int idCount;
        std::map<std::string,int> idTable;
        std::map<int,std::string> ridTable;
        std::vector<int>* data;
};

#endif
