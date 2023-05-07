#pragma once

#include <map>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

class Search {

private:
    //std::vector<std::string> paths;
    std::map<std::string, size_t> words;
    std::map<std::string, std::map<size_t, size_t>> dictionary;
    std::vector<std::string> vecPaths1;
public:
    size_t max_response = 5;
    std::mutex myMutex;

    struct RI {
        size_t ind;
        size_t sum;
        RI(size_t a, size_t b) : ind(a), sum(b) { };
    };

    std::map<std::string, size_t> getWords(const std::string &path);
    std::vector<std::string> getSearchPaths(const std::string &dir);
    std::map<std::string, std::map<size_t, size_t>> getDictionary();
    void setDictionary(const std::vector<std::string>& vecPaths);
    std::vector<RI> find(std::string s);
};
