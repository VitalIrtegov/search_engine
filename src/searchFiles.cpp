
#include "../include/searchFiles.h"
#include <iostream>
#include <fstream>
#include <boost/tokenizer.hpp>

void Search::setSearch() {
    std::ifstream in("C:/drugs/beta.txt");

    //std::cout << "open" << std::endl;
    std::string line;

    if (in.is_open()) {
        //std::cout << "read" << std::endl;
        typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
        boost::char_separator<char> sep("-;|, :\"\'.");

        while (getline(in, line)) {
            tokenizer tokens(line, sep);
            for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter) {
                std::cout << "<" << *tok_iter << "> ";
            }
            //std::cout << line << std::endl;
        }
    }

    in.close();
}

std::set<std::string> Search::getSearch() {
    //std::set<std::string> temp;
    return words;
}
