
#include "../include/searchFiles.h"
#include <iostream>
#include <fstream>
#include <boost/tokenizer.hpp>

void Search::setSearch() {
    std::ifstream file("C:/drugs/beta.txt");
    std::string line;

    if (file.is_open()) {
        typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
        boost::char_separator<char> sep("-);|(, :\"\'./[]!_?><%");

        while (getline(file, line)) {
            std::transform(line.begin(), line.end(), line.begin(), tolower);
            tokenizer tokens(line, sep);
            for (tokenizer::iterator iter = tokens.begin(); iter != tokens.end(); ++iter) {
                words.emplace(*iter, words[*iter]++);
            }
        }
    }
    file.close();
}




std::map<std::string, size_t> Search::getSearch() {
    return words;
}

//std::vector<int, std::map<std::string, size_t>> vector;