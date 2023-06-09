#include <iostream>
#include "include/searchFiles.h"
#include <filesystem>
#include <string>
#include <vector>


int main() {
    std::string dir = "C:/drugs2/";

    Search search;

    std::vector<std::string> vecPaths = search.getSearchPaths(dir);

    //std::string str = "after";  // after, crazy
    search.setDictionary(vecPaths);

    std::map<std::string, std::map<size_t, size_t>> dictionary = search.getDictionary();

   /* for (const auto& i : dictionary) {
        std::cout << i.first << ", ";
        for (auto j : i.second) {
            std::cout << "<" << j.first << ">, <" << j.second << ">" << std::endl;
        }
    }/**/

    auto m = search.find("awesome years and");
    for(auto &j : m)
        std::cout << "" << vecPaths[j.ind] << " - " << j.sum << "" << std::endl;
}

/*std::vector<std::string> vecPaths = search.getSearchPaths(dir);

    for (auto i: vecPaths) {
        std::map<std::string, size_t> words = search.getWords(i);
    }*/

    /*search.setSearch();
    std::map<std::string, size_t> map = search.getSearch();

    for (auto item : map) {
        std::cout << item.first << ", " << item.second << std::endl;
    }*/