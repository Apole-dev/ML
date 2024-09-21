cmake_minimum_required(VERSION 3.28)
project(ML)

set(CMAKE_CXX_STANDARD 17)

add_executable(ML main.cpp
        Data/Data.cpp
        Data/Data.h
        "Data Hub/DataHub.cpp"
        "Data Hub/DataHub.h"
        "KNN Algorithm/KNN.cpp"
        "KNN Algorithm/KNN.h"
)
