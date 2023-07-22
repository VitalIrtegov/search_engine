
#include <iostream>
#include "include/SearchServer.h"
#include "include/InvertedIndex.h"
#include "include/ConverterJSON.h"

int main() {
    ConverterJSON::readSettings("../resources/config.json");
    Settings::getInstance().showSettings();

    std::vector<std::string> vecPaths = Settings::getInstance().files;
    InvertedIndex::getInstance().updateDocumentBase(vecPaths);

    vectorRes res = SearchEngine::getInstance().getAnswers(ConverterJSON::getRequests("../resources/requests.json"));
    ConverterJSON::writeAnswers(res, "../resources/answers.json");
}
