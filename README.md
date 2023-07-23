# search_engine

## Description | Описание
Консольное приложение для поиска слов в текстовых файлах (config.json) по заросу из файла (requests.json)<br>
Результат поиска записывается в answers.json.<br>

Для правильной работы программы потребуется установить библиотеку boost версии 1_81_0

Документация:
https://www.boost.org/doc/libs/1_81_0/

Файлы:
https://boostorg.jfrog.io/artifactory/main/release/1.81.0/source/

В проекте используюся следующие ресурсы:<br>

[C++17](https://en.cppreference.com/w/cpp/17)<br>

[CMake 3.23](https://cmake.org/cmake/help/latest/release/3.23.html)<br>

[Nlohmann JSON](https://github.com/nlohmann/json)<br>

[GoogleTest](https://github.com/google/googletest)<br>

<h3>Формат записи config.json</h3>

```json
{
  "config": {
    "name": "SkillboxSearchEngine",
    "version": "0.1",
    "max_responses": 5
  },
  "files": [
    "resources/file001.txt",
    "resources/file002.txt",
    "resources/file003.txt",
    "resources/file004.txt"
  ]
}
```
