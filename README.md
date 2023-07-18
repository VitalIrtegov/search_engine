# search_engine

Для правильной работы программы потребуется установить библиотеку boost версии 1_81_0

Документация:
https://www.boost.org/doc/libs/1_81_0/

Файлы:
https://boostorg.jfrog.io/artifactory/main/release/1.81.0/source/

После скачивания архива с библиотекой, распаковываем его на Локальный диск (лучше) С.<br/>
Открываем папку boost_1_81_0 и запускаем файл bootstrap.bat<br/>
После того как bootstrap.bat отработает, в папке появится файл b2.exe<br/>
Запускаем b2.exe и ждем от 5 минут до 1,5 часа (зависит от компьютера)<br/>
Когда b2.exe отработает, ваша библиотека будет в собранном состоянии,<br/>
осталось только её подключить в вашу IDE.<br/>

В файл CMakeLists записываем:

set(Boost_INCLUDE_DIR C:/boost_1_81_0/)<br/>
set(Boost_LIBRARY_DIR C:/boost_1_81_0/stage/lib)<br/>
