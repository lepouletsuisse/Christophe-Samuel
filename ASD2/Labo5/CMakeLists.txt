cmake_minimum_required(VERSION 3.2)
project(Labo5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    AVLTree.h
    main.cpp)

add_executable(Labo5 ${SOURCE_FILES})