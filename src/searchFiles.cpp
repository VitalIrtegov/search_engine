
#include "../include/searchFiles.h"
#include "../include/InvertedIndex.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <set>
#include <boost/tokenizer.hpp>
#include <filesystem>
#include <functional>

namespace fs = std::filesystem;

std::vector<std::string> SearchEngine::getSearchPaths(const std::string &dir) {
    auto recursiveGetFileNamesByExtension = [](const std::string &path) {
        std::vector<std::string> paths;
        for(auto &p: fs::recursive_directory_iterator(path))
            if(p.is_regular_file() && p.path().extension().compare("txt") != 0) {
                paths.push_back(p.path().string());
            }
        return paths;
    };
    return std::move(recursiveGetFileNamesByExtension(dir));
}

std::vector<RelativeIndex> SearchEngine::find(std::string line) {
    std::set<std::string> tempDictionary;
    typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
    boost::char_separator<char> sep("-);|(, :\"\'./[]!_?><%");

    std::transform(line.begin(), line.end(), line.begin(), tolower);
    tokenizer tokens(line, sep);
    for (tokenizer::iterator iter = tokens.begin(); iter != tokens.end(); ++iter)
        tempDictionary.insert(*iter);

    std::vector<RelativeIndex> vec;
    std::vector<RelativeIndex> vecOutput;
    std::map<size_t, size_t> map;

    for (const auto &item : tempDictionary) {
        if(auto it = InvertedIndex::getInstance().dictionary.find(item); it != InvertedIndex::getInstance().dictionary.end())
        for (const auto &i :it->second) {
            map[i.first] += i.second;
        } else {
            return std::vector<RelativeIndex>{};
        }
    }
    for (const auto &w: map)
        vec.emplace_back(w.first, w.second);

    std::sort(vec.begin(), vec.end(), [](const auto &a, const auto &b) { return b.sum < a.sum; });

    max_response = Settings::getInstance().max_response;

    max_response = max_response > vecOutput.size() ? max_response : vecOutput.size();

    for (int i = 0; i < max_response; i++)
        vecOutput.push_back(vec[i]);

    if(vecOutput.empty())
        return std::vector<RelativeIndex>{};

    size_t maxSum = vecOutput.begin()->sum;

    for (auto &i : vecOutput)
        i.rankInd =  (float) i.sum / (float) maxSum;

    return vecOutput;
}

vectorRes SearchEngine::getAnswers(std::vector<std::string> req) {
    vectorRes res;
    for(int i = 1;i <= req.size(); i++) {
        std::string request = "request";
        request += i < 10 ? "00" + std::to_string(i) : i < 100 ? "0" + std::to_string(i) : std::to_string(i);
        res.push_back(std::make_pair(request, find(req[i-1])));
    }
    return res;
}

Settings &Settings::getInstance() {
    static Settings settings;
    return settings;
}

void Settings::showSettings() const {
    std::cout << "Name: " << name << std::endl;
    std::cout << "Version: " << version << std::endl;
    std::cout << "Max_response: " << max_response << std::endl;
}
