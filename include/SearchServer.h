#pragma once

#include <map>
#include <string>
#include <vector>
#include <thread>

/***  ***/
struct RelativeIndex {
    size_t ind;
    size_t sum;
    float rankInd;
    RelativeIndex(size_t a, size_t b) : ind(a), sum(b), rankInd{} {};
};

/***  ***/
struct Settings {
    std::string name;
    std::string version;
    size_t max_response;
    std::vector<std::string> files;

    void showSettings() const;
    static Settings &getInstance();
};

typedef std::vector<std::pair<std::string, std::vector<RelativeIndex>>> vectorRes;

class SearchEngine {
private:
    size_t max_response;
    SearchEngine() = default;
public:
    /***  ***/
    std::vector<RelativeIndex> find(std::string s);

    /***  ***/
    vectorRes getAnswers(std::vector<std::string> req);

    static SearchEngine &getInstance () {
        static SearchEngine instance;
        return instance;
    }
};
