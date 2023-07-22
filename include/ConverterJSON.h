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
    /*** структура с  исключениями ***/
    struct myExp : public std::exception {
    public:
        std::string file;
        myExp() = default;
        explicit myExp(std::string _file) : file(std::move(_file)) {};
        void show() const { std::cout << "Error pars settings '" << file << "'" << std::endl; }
    };

    /*** прочитать файл конфигурации config.json ***/
    static void readSettings(const std::string &jsonPath);

    /*** прочитать файл с запросами requests.json ***/
    static std::vector<std::string> getRequests(const std::string &jsonPath);

    /*** запись результата в файл answers.json ***/
    static void writeAnswers(const myRes &answers, const std::string &jsonPath);
};

