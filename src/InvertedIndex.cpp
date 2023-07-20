//
// Created by Vital on 08.05.2023.
//

#include "../include/InvertedIndex.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <sstream>
#include <boost/tokenizer.hpp>
#include <functional>

std::map<std::string, size_t> InvertedIndex::getWords(const std::string &path) {

    std::map<std::string, size_t> words;

#ifndef TEST
    std::ifstream file(path);
    if(!file.is_open())
        return std::map<std::string, size_t>();

    std::string text((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
    std::istringstream isText(text);
    file.close();
#else
    std::istringstream isText(path);
#endif
    std::string line;

    typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
    boost::char_separator<char> sep("-);|(, :\"\'./[]!_?><%");

    while (isText) {
        isText >> line;
        if (!isText)
            break;

        std::transform(line.begin(), line.end(), line.begin(), tolower);
        tokenizer tokens(line, sep);
        for (tokenizer::iterator iter = tokens.begin(); iter != tokens.end(); ++iter) {
            words.emplace(*iter, words[*iter]++);
        }
    }

    return std::move(words);
}

void InvertedIndex::updateDocumentBase(const std::vector<std::string> &_paths) {
    std::map<size_t, size_t> map;

    paths = _paths;
    std::vector<std::thread> vecTh;

    auto myIndexation = [this](size_t ind) {
        std::map<std::string, size_t> res = getWords(paths[ind]);

        for (const auto &index: res) {
            std::lock_guard<std::mutex> lock(myMutex);
            dictionary[index.first].insert(std::make_pair(ind, index.second));
        }
    };

    auto t1 = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < paths.size(); ++i) {
        vecTh.emplace_back(myIndexation, i);
    }

    for (auto &t: vecTh)
        t.join();

    auto t2 = std::chrono::high_resolution_clock::now();
    auto t3 = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

    std::cout << "time " << t3 << std::endl;
    //612
    //2158
}

InvertedIndex &InvertedIndex::getInstance() {
    static InvertedIndex instance;
    return instance;
}

std::map<size_t, size_t> InvertedIndex::getWordCount(const std::string &s) {
    auto f = dictionary.find(s);
    if (f != dictionary.end())
        return (*f).second;
    else
        return std::map<size_t, size_t>{};
}
