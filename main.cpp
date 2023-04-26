#include <iostream>
#include "include/searchFiles.h"

int main() {
    Search search;
    search.setSearch();
    std::set<std::string> set = search.getSearch();

    for (std::string item : set) {
        std::cout << item << std::endl;
    }
}