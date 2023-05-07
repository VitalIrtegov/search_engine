
#include "../include/searchFiles.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <boost/tokenizer.hpp>
#include <filesystem>
#include <functional>

namespace fs = std::filesystem;

std::vector<std::string> Search::getSearchPaths(const std::string &dir) {
    auto recursiveGetFileNamesByExtension = [](const std::string &path) {
        std::vector<std::string> paths;
        for(auto &p: fs::recursive_directory_iterator(path))
            if(p.is_regular_file() && p.path().extension().compare("txt") != 0) {
                paths.push_back(p.path().string());
                //std::cout << p.path().string() << std::endl;
            }
        return paths;
    };
    return std::move(recursiveGetFileNamesByExtension(dir));
}

std::map<std::string, size_t> Search::getWords(const std::string &path) {
    //std::map<std::string, size_t> words;
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

    return std::move(words);
}

void Search::setDictionary(const std::vector<std::string> &vecPaths) {
    std::map<size_t, size_t> map;
    //map.insert(std::make_pair(t1, t2));

    vecPaths1 = vecPaths;
    int c = std::thread::hardware_concurrency();
    std::vector<std::thread> vecTh;
    //mypool pool(c);

    auto myIndexation = [this](size_t ind) {
        std::map<std::string, size_t> res = getWords(vecPaths1[ind]);

        for(const auto &ii: res) {
            std::lock_guard<std::mutex> lock(myMutex);
            dictionary[ii.first].insert(std::make_pair(ind, ii.second));
        }
    };

    auto t1 = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < vecPaths.size(); ++i) {
        vecTh.emplace_back(myIndexation, i);
    }   // myIndexation(i);

    for(auto &t : vecTh)
        t.join();

    auto t2 = std::chrono::high_resolution_clock::now();
    auto t3 = std::chrono::duration_cast<std::chrono::milliseconds > (t2-t1).count();

    std::cout << "time " << t3 << std::endl ;

    //612
    //2158
}

std::map<std::string, std::map<size_t, size_t>> Search::getDictionary() {
    return dictionary;
}

std::vector<Search::RI> Search::find(std::string line) {
    std::map<std::string, size_t> res;
    typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
    boost::char_separator<char> sep("-);|(, :\"\'./[]!_?><%");

    std::transform(line.begin(), line.end(), line.begin(), tolower);
    tokenizer tokens(line, sep);
    for (tokenizer::iterator iter = tokens.begin(); iter != tokens.end(); ++iter)
        res.emplace(*iter, res[*iter]++);

    std::vector<RI> v;
    std::vector<RI> vRes;
    std::map<size_t, size_t> m;

    for (const auto &w : res) {
        for (const auto &i : dictionary.at(w.first)) {
            m[i.first] += i.second;
        }
    }
    for(const auto &w : m)
        v.emplace_back(w.first, w.second);

    std::sort(v.begin(), v.end(), [](const auto &a, const auto &b){return b.sum < a.sum;});

    int c = max_response > vRes.size() ? max_response : vRes.size();

    for(int i = 0; i < c; i++)
        vRes.push_back(v[i]);

    return vRes;
}
