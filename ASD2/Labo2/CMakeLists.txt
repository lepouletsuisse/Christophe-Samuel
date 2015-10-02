cmake_minimum_required(VERSION 3.2)
project(Labo2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Sources/DiGraph.cpp
    Sources/DiGraph.h
    Sources/DirectedCycle.h
    Sources/main.cpp
    Sources/ParcoursEnProfondeur.h
    Sources/prerequis.txt
    Sources/prerequis2.txt
    Sources/SymbolGraph.h
    Sources/TopologicalSort.h
    Sources/Util.cpp
    Sources/Util.h)

add_executable(Labo2 ${SOURCE_FILES})