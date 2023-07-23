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
private:
    std::map<std::string, std::map<size_t, size_t>> dictionary;
    std::vector<std::string> paths;
    std::mutex myMutex;

    /**
     * метод находит количество вхождений слова в тексте
     * @return возвращает количество вхождений
     */
    std::map<std::string, size_t> getWords(const std::string &path);

    friend class SearchEngine;

public:
    /**
     * обновление и заполнение базы документов для поиска
    */
    void updateDocumentBase(const std::vector<std::string> &paths);

    static InvertedIndex &getInstance ();
};