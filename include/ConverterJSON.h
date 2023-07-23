//
// Created by Vital on 08.05.2023.
//

#pragma once

#include <fstream>
#include <utility>
#include <list>
#include <iostream>
#include <nlohmann/json.hpp>
#include <exception>

struct RelativeIndex;

typedef std::vector<std::pair<std::string, std::vector<RelativeIndex>>> myRes;

class ConverterJSON {
public:
    /**
     * метод читает файл конфигурации config.json/
     */
    static void readSettings(const std::string &jsonPath);

    /**
     * метод читает файл с запросами requests.json
     * @return возвращает список запросов
     */
    static std::vector<std::string> getRequests(const std::string &jsonPath);

    /**
     * метод записывает результаты в файл answers.json
     */
    static void writeAnswers(const myRes &answers, const std::string &jsonPath);
};
