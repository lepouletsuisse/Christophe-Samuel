cmake_minimum_required(VERSION 3.2)
project(Labo3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Sources/EdgeWeightedDigraph.h
    Sources/EdgeWeightedGraph.h
    Sources/EdgeWeightedGraphCommon.h
    Sources/main.cpp
    Sources/MinimumSpanningTree.h
    Sources/RoadNetwork.cpp
    Sources/RoadNetwork.h
    Sources/ShortestPath.h
    Sources/UnionFind.cpp
    Sources/UnionFind.h
    Sources/Util.cpp
    Sources/Util.h)

add_executable(Labo3 ${SOURCE_FILES} Sources/RoadGraphWrapper.h)