
#include "../include/searchFiles.h"
#include <iostream>
#include <fstream>
#include <boost/tokenizer.hpp>
#include <filesystem>
#include <functional>

namespace fs = std::filesystem;

std::vector<std::string> Search::getSearchPaths(const std::string &dir) {
    auto recursiveGetFileNamesByExtension = [](const std::string &path) {
        std::vector<std::string> paths;
        for(auto &p: fs::recursive_directory_iterator(path))
            if(p.is_regular_file() && p.path().extension().compare("txt") != 0)
                paths.push_back(p.path().string());
        return paths;
    };
    return std::move(recursiveGetFileNamesByExtension(dir));
}

std::map<std::string, size_t> Search::getWords(const std::string &path) {
    std::map<std::string, size_t> words;
    std::ifstream file(path);
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
    return words;
}

void Search::setDictionary(std::string &str, size_t &t1, size_t &t2) {
    std::map<size_t, size_t> map;
    map.insert(std::make_pair(t1, t2));
    dictionary.insert(std::make_pair(str, map));
}

std::map<std::string, std::map<size_t, size_t>> Search::getDictionary() {
    return dictionary;
}
