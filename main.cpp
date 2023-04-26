#include <iostream>
#include "include/searchFiles.h"

int main() {
    Search search;
    search.setSearch();
    std::map<std::string, size_t> map = search.getSearch();

    for (auto item : map) {
        std::cout << item.first << ", " << item.second << std::endl;
    }
}