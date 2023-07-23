#pragma once

#include <map>
#include <string>
#include <vector>
#include <thread>

/**
 * структура хранения реливантности документов
 */
struct RelativeIndex {
    size_t ind;
    size_t sum;
    float rankInd;
    RelativeIndex(size_t a, size_t b) : ind(a), sum(b), rankInd{} {};
};

/**
 * структура хранения кофгурации файлов
 */
struct Settings {
    std::string name;
    std::string version;
    size_t max_response;
    std::vector<std::string> files;

    void showSettings() const;

    static Settings &getInstance();
};

typedef std::vector<std::pair<std::string, std::vector<RelativeIndex>>> vectorRes;

class SearchEngine {
private:
    size_t max_response;

    /**
     * метод расчета и сортировки относительного индекса
     * @return возвращает отсортированный в порядке убывания контейнер с относительным индексом
     */
    std::vector<RelativeIndex> find(std::string s);
    SearchEngine() = default;
public:
    /**
     * метод формирования контейнера по количеству запросов
     * @return возвращает контейнер с относительным индексом по запросам
     */
    vectorRes getAnswers(std::vector<std::string> req);

    void setMaxResponse(size_t maxResponse);

    static SearchEngine &getInstance () {
        static SearchEngine instance;
        return instance;
    }
};
