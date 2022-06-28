cmake_minimum_required(VERSION 3.22)
project(CS201_Hw3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CS201_Hw3
        .idea/.gitignore
        .idea/CS201_Hw3.iml
        .idea/modules.xml
        .idea/workspace.xml
        main.cpp
        PuzzleContainer.cpp
        PuzzleContainer.h
        PuzzleRow.h
        PuzzleRow.cpp)
