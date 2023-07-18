#include <iostream>
#include "include/searchFiles.h"
#include "include/InvertedIndex.h"
#include "include/ConvertJSON.h"

int main() {
    //std::string dir = "C:/textTest/";

    ConvertJSON::readSettings("../resources/config.json");
    Settings::getInstance().showSettings();

    //std::vector<std::string> vecPaths = SearchEngine::getInstance().getSearchPaths(dir);

    std::vector<std::string> vecPaths = Settings::getInstance().files;
    InvertedIndex::getInstance().updateDocumentBase(vecPaths);

    vectorRes res = SearchEngine::getInstance().getAnswers(ConvertJSON::getRequests("../resources/requests.json"));

    ConvertJSON::writeAnswers(res, "../resources/answers.json");

    //system("pause");
}

