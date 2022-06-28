cmake_minimum_required(VERSION 3.21)
project(CS201_Hw1)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(CS201_Hw1
        include/Lot.h
        include/main.h
        include/ParkingSystem.h
        src/Lot.cpp
        src/main.cpp
        src/ParkingSystem.cpp src/Car.cpp include/Car.h)
