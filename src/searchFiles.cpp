
#include "../include/searchFiles.h"
#include <iostream>
#include <fstream>

void Search::setSearch() {
    std::ifstream in("C:/drugs/beta.txt");

    std::cout << "open" << std::endl;
    std::string line;

    if (in.is_open()) {
        std::cout << "read" << std::endl;
        while (getline(in, line))
        {
            std::cout << line << std::endl;
        }
    }

    in.close();
}

std::set<std::string> Search::getSearch() {
    //std::set<std::string> temp;
    return words;
}
