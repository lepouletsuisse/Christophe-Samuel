cmake_minimum_required(VERSION 3.2)
project(Labo6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    check.cpp
    check.h
    main.cpp
    TST.cpp
    TST.h
    Util.h
    WordDictionnary.cpp
    WordDictionnary.h)

add_executable(Labo6 ${SOURCE_FILES})