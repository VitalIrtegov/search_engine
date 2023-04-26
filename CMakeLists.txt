cmake_minimum_required(VERSION 3.23)
project(search_engine)

set(CMAKE_CXX_STANDARD 17)

set(Boost_INCLUDE_DIR C:/boost_1_81_0/)
set(Boost_LIBRARY_DIR C:/boost_1_81_0/stage/lib)

find_package(Boost COMPONENTS REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})
link_libraries(ws2_32 wsock32)

add_executable(search_engine main.cpp include/searchFiles.h src/searchFiles.cpp)

target_link_libraries(search_engine ${Boost_LIBRARIES})

if(MINGW)
    target_link_libraries(search_engine ws2_32 )
endif()
