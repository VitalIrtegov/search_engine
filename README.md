# search_engine

## Описание
SearchEngine - консольное приложение для поиска слов в текстовых файлах (config.json) по заросу из файла (requests.json)<br>
Результат поиска записывается в answers.json.<br>

В проекте используюся следующие ресурсы:<br>

[C++17](https://en.cppreference.com/w/cpp/17)<br>

[CMake 3.23](https://cmake.org/cmake/help/latest/release/3.23.html)<br>

[Nlohmann JSON](https://github.com/nlohmann/json)<br>

[GoogleTest](https://github.com/google/googletest)<br>

Для правильной работы программы потребуется установить библиотеку boost версии 1_81_0<br>

[Documentation](https://www.boost.org/doc/libs/1_81_0/)<br>

[Files](https://boostorg.jfrog.io/artifactory/main/release/1.81.0/source/)<br>

<h4>Формат записи config.json</h4>

```json
{
  "config": {
    "name": "SkillboxSearchEngine",
    "version": "0.1",
    "max_responses": 5
  },
  "files": [
    "../resources/file001.txt",
    "../resources/file002.txt",
    "../resources/file003.txt",
    "../resources/file004.txt",
    ...
  ]
}
```
config - общая информация, обязательно для заполнения.<br>
name - наименование SearchEngine.<br>
version - номер версии SearchEngine.<br>
max_responses - поле, определяющее максимальное количество ответов на один запрос.<br>
files - пути к файлам, по которым необходимо осуществлять поиск.<br>

<h4>Формат записи requests.json</h4>

```json
{
  "requests": [
    "word",
    "some words..",
    "some words..",
    "some words..",
    ...
  ]
}
```
requests - запросы, обязательно для заполнения.<br>
далее перечисление слов.<br>

<h4>Формат записи answers.json</h4>

```json
{
  "Answers": {
    "request001": {
      "relevance": [
        {
          "docid": 12,
          "rank": 1.0
        },
        {
          "docid": 25,
          "rank": 0.875
        }
      ],
      "result": true
    },
    "request002": {
      "relevance": [
        {
          "docid": 27,
          "rank": 1.0
        },
        {
          "docid": 22,
          "rank": 0.75
        }
      ],
      "result": true
    },
    "request003": {
      "result": false
    }
  }
}

```
Answers - ответы, обязательно для заполнения.<br>
request001, request002 и request003 - идентификатор запроса, по которому сформирован ответ.<br>
result – результат поиска запроса. Если он принимает значение true, значит по<br>
данному запросу найден хотя бы один документ.<br>
relevance - включается в файл answers.json, если на этот запрос удалось найти<br>
более одного документа.<br>
docid — идентификатор документа, в котором найден ответ на запрос.<br>
Он формируется автоматически при индексации всех документов по порядку.<br>
rank — поисковый рейтинг. Число показывает, насколько документ подходит для заданного запроса.<br>