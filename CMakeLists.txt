cmake_minimum_required(VERSION 3.27)
project(CPP_Bug_Project_RF)

set(CMAKE_CXX_STANDARD 17)

add_executable(CPP_Bug_Project_RF main.cpp
        sources/Bug.cpp
        headers/Bug.h
        headers/Direction.h
        headers/Crawler.h
        sources/Crawler.cpp
        sources/Hopper.cpp
        headers/Hopper.h
        sources/Board.cpp
        headers/Board.h
        sources/Knight.cpp
        headers/Knight.h
        sources/SuperBug.cpp
        headers/SuperBug.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML-2.6.1/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML-2.6.1/include)
target_link_libraries(CPP_Bug_Project_RF sfml-system sfml-window sfml-graphics sfml-audio)