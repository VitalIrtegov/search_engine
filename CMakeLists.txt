cmake_minimum_required(VERSION 3.23)
project(search_engine)

set(CMAKE_CXX_STANDARD 17)

set(Boost_INCLUDE_DIR C:/boost_1_81_0/)
set(Boost_LIBRARY_DIR C:/boost_1_81_0/stage/lib)

find_package(Boost COMPONENTS REQUIRED)

include(FetchContent)
Set(FETCHCONTENT_QUIET FALSE)
set(JSON_BuildTests OFF CACHE INTERNAL "")

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})
link_libraries(ws2_32 wsock32)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.12.0
)

FetchContent_MakeAvailable(googletest)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz)
FetchContent_MakeAvailable(json)

add_executable(search_engine main.cpp include/SearchServer.h src/SearchServer.cpp src/InvertedIndex.cpp include/InvertedIndex.h
        include/ConverterJSON.h src/ConverterJSON.cpp)

target_link_libraries(search_engine PUBLIC ${Boost_LIBRARIES} nlohmann_json::nlohmann_json)

if(MINGW)
    target_link_libraries(search_engine PRIVATE ws2_32 )
endif()

project(search_engine_test)

include(GoogleTest)

enable_testing()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_executable(search_engine_test main_test.cpp include/SearchServer.h src/SearchServer.cpp src/InvertedIndex.cpp include/InvertedIndex.h
        include/ConverterJSON.h src/ConverterJSON.cpp)

target_link_libraries(search_engine_test PUBLIC gtest gtest_main nlohmann_json::nlohmann_json)

option(TEST "option for debug" OFF)

if (TEST)
    add_definitions(-DTEST)
endif(TEST)

gtest_discover_tests(search_engine_test)