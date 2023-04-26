cmake_minimum_required(VERSION 3.23)
project(search_engine)

set(CMAKE_CXX_STANDARD 17)

add_executable(search_engine main.cpp include/searchFiles.h src/searchFiles.cpp)