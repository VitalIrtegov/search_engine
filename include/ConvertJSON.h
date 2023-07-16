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

class ConvertJSON {
public:

    struct myExp : public std::exception {
    public:
        std::string file;
        myExp() = default;
        explicit myExp(std::string _file) : file(std::move(_file)) {};
        void show() const { std::cout << "Error pars settings '" << file << "'" << std::endl; }
    };

    // static void setSettings(const search_server::Settings& val);
    static void readSettings(const std::string &jsonPath);
    static std::vector<std::string> getRequests(const std::string &jsonPath);
    // static std::vector<std::string> getRequestsFromString(const std::string& jsonString);
    static void writeAnswers(const myRes &answers, const std::string &jsonPath);
};

