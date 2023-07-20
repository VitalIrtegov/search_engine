//
// Created by user on 04.02.2023.
//

#include "../include/ConverterJSON.h"
#include "../include/SearchServer.h"

/****************** метод чтения config.json файла *****************/
void ConverterJSON::readSettings(const std::string &jsonPath) {
    nlohmann::json jsonSettings;
    std::ifstream jsonFileSettings(jsonPath);

    try {
        jsonSettings = nlohmann::json::parse(jsonFileSettings);
        jsonFileSettings.close();

        jsonSettings.at("files").get_to(Settings::getInstance().files);
        jsonSettings.at("config").at("Name").get_to(Settings::getInstance().name);
        jsonSettings.at("config").at("Version").get_to(Settings::getInstance().version);
        jsonSettings.at("config").at("max_response").get_to(Settings::getInstance().max_response);

    } catch (nlohmann::json::parse_error &exp) {
        std::cerr << "JSON parse error " << exp.byte << std::endl;
        throw myExp(jsonPath);
    }
}

std::vector<std::string> ConverterJSON::getRequests(const std::string &jsonPath) {

    std::vector<std::string> requests;
    nlohmann::json jsonRequests;
    std::ifstream jsonFileRequests(jsonPath);

    try {
        jsonRequests = nlohmann::json::parse(jsonFileRequests);
        jsonFileRequests.close();
    } catch (nlohmann::json::parse_error &exp) {
        std::cerr << "JSON parse error " << exp.byte << std::endl;
        jsonFileRequests.close();
        return std::move(requests);
    }

    jsonRequests.at("Requests").get_to(requests);
    return requests;
}

void to_json(nlohmann::json &j, const RelativeIndex &relativeIndex) {
    j = nlohmann::json{
        {"docid", relativeIndex.ind},
        {"rank", relativeIndex.rankInd}
    };
}

/****************** метод записи JSON файлов *****************/
void ConverterJSON::writeAnswers(const myRes &answers, const std::string &jsonPath) {
    nlohmann::json jsonAnswers;

    for(const auto &answer: answers) {
        jsonAnswers["Answers"][answer.first]["result"] = !answer.second.empty();
        if (!answer.second.empty()) {
            jsonAnswers["Answers"][answer.first]["relevance"] = answer.second;
        }
    }

    std::ofstream jsonFile(jsonPath);

    jsonFile << std::setw(2) << jsonAnswers;
    jsonFile.close();
}
