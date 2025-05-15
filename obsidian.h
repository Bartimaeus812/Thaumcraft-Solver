#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <map>

class Obsidian {
    public:
        Obsidian(std::string path, bool isFileNotFolder);
        struct nodeInfo {
            int count {0};
            int maxCount {0};
        };
        void inputCounts();
        void calculateMaxCounts();
        const std::map<std::string,std::pair<std::string,std::string>*> GetNodes() const;
        const std::map<std::string,nodeInfo*> GetData() const;
        void FileOutput(std::string path) const;
    private:
        int getDepth(std::string s) const;
        std::map<std::string,std::pair<std::string,std::string>*> nodes;
        std::map<std::string,nodeInfo*> nodeData;
};