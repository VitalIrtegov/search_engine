#pragma once

#include <set>
#include <string>

class Search {
private:
    std::set<std::string> words;
public:
    Search () { };
    void setSearch();
    std::set<std::string> getSearch();
};

