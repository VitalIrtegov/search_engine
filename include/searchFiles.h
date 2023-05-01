#pragma once

#include <map>
#include <string>
#include <vector>

class Search {
private:
    //std::vector<std::string> paths;
    std::map<std::string, size_t> words;
    std::map<std::string, std::map<size_t, size_t>> dictionary;
public:
    std::map<std::string, size_t> getWords(const std::string &path);
    std::vector<std::string> getSearchPaths(const std::string &dir);
    std::map<std::string, std::map<size_t, size_t>> getDictionary();
    void setDictionary(std::string &str, std::vector<std::string> vecPaths);
};
