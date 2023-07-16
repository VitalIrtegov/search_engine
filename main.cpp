#include <iostream>
#include "include/searchFiles.h"
#include "include/InvertedIndex.h"
#include "include/ConvertJSON.h"

int main() {
    //std::string dir = "C:/textTest/";

    ConvertJSON::readSettings("config.json");
    Settings::getInstance().showSettings();

    //std::vector<std::string> vecPaths = SearchEngine::getInstance().getSearchPaths(dir);

    std::vector<std::string> vecPaths = Settings::getInstance().files;
    InvertedIndex::getInstance().updateDocumentBase(vecPaths);

    vectorRes res = SearchEngine::getInstance().getAnswers(ConvertJSON::getRequests("Requests.json"));

    ConvertJSON::writeAnswers(res, "Answers.json");

    //system("pause");
}

