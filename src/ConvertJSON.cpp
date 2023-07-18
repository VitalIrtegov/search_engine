//
// Created by user on 04.02.2023.
//

#include "../include/ConvertJSON.h"
#include "../include/searchFiles.h"

/****************** метод чтения config.json файла *****************/
void ConvertJSON::readSettings(const std::string &jsonPath) {
    nlohmann::json jsonSettings;
    std::ifstream jsonFileSettings(jsonPath);

    try {
        jsonSettings = nlohmann::json::parse(jsonFileSettings);
        jsonFileSettings.close();

        jsonSettings.at("files").get_to(Settings::getInstance().files);
        jsonSettings.at("config").at("Name").get_to(Settings::getInstance().name);
        jsonSettings.at("config").at("Version").get_to(Settings::getInstance().version);
        jsonSettings.at("config").at("max_response").get_to(Settings::getInstance().max_response);
        //jsonSettings.at("config").at("dir").get_to(Settings::getInstance().dir);

    } catch (nlohmann::json::parse_error &exp) {
        std::cerr << "JSON parse error " << exp.byte << std::endl;
        throw myExp(jsonPath);
    }
}

/****************** метод *****************/
std::vector<std::string> ConvertJSON::getRequests(const std::string &jsonPath) {

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
void ConvertJSON::writeAnswers(const myRes &answers, const std::string &jsonPath) {
    nlohmann::json jsonAnswers;

    for(const auto &answer: answers) {
        jsonAnswers["Answers"][answer.first]["result"] = !answer.second.empty();
        jsonAnswers["Answers"][answer.first]["relevance"] = answer.second;
    }

    std::ofstream jsonFile(jsonPath);

    jsonFile << std::setw(2) << jsonAnswers;
    jsonFile.close();
}

/*std::vector<std::string> ConvertJSON::getRequestsFromString(const std::string &jsonString) {

    std::vector<std::string> requests;
    nh::json jsonRequests;

    try
    {
        jsonRequests = nh::json::parse(jsonString);
    }
    catch (nh::json::parse_error& ex)
    {
        std::cerr << "JSON parse error (getRequestsFromString) at byte " << ex.byte << std::endl;
        return std::move(requests);
    }

    jsonRequests.at("Requests").get_to(requests);

    return requests;
}*/