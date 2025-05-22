#ifndef OBSIDIAN_H
#define OBSIDIAN_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <map>
#include <algorithm>
#include <vector>

class Obsidian {
    public:
        Obsidian(std::string path, bool isFileNotFolder = true);
        struct nodeInfo {
            int count {0};
            int maxCount {0};
        };
        void inputCounts();
        const std::map<std::string,std::pair<std::string,std::string>> getNodes() const;
        const std::map<std::string,nodeInfo> getData() const;
        void fileOutput(std::string path) const;
    private:
        std::map<std::string,std::pair<std::string,std::string>> nodes;
        std::map<std::string,nodeInfo> nodeData;
};

#endif
