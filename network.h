#ifndef NETWORK_H
#define NETWORK_H

#include <map>
#include <string>
#include <vector>

class Network {
    public:
        Network() {}
        Network(const std::map<std::string,std::pair<std::string,std::string>*> nodes);
        
        std::vector<int> operator[](int i);
        
        int toInt(std::string s) const {return idTable.at(s);}
        std::string toString(int i) const {return ridTable.at(i);}
        size_t size() {return _size;}
    private:
        size_t _size;
        int idCount;
        int addId(std::string s);
        std::map<std::string,int> idTable;
        std::map<int,std::string> ridTable;
        std::vector<int>* data;
};

#endif
