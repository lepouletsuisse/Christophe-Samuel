set(SOURCE_FILES
    ex2.cpp
    GraphUsingAdjacencyLists.cpp
    GraphUsingAdjacencyLists.h
    Util.cpp
    ParcoursEnLargeur.h
    SymbolGraph.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(Partie_2 ${SOURCE_FILES})