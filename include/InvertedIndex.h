//
// Created by Vital on 08.05.2023.
//
#pragma once

#include <map>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

class InvertedIndex {
    std::map<std::string, std::map<size_t, size_t>> dictionary;
    std::vector<std::string> paths;
    std::mutex myMutex;
    std::map<std::string, size_t> getWords(const std::string &path);
    friend class SearchEngine;

public:
    void updateDocumentBase(const std::vector<std::string> &paths);
    std::map<size_t,size_t> getWordCount(const std::string &s);
    static InvertedIndex &getInstance ();
};