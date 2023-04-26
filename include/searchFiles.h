#pragma once

#include <map>
#include <string>

class Search {
private:
    std::map<std::string, size_t> words;
public:
    Search () { };
    void setSearch();
    std::map<std::string, size_t> getSearch();
};

