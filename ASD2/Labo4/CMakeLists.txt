cmake_minimum_required(VERSION 3.2)
project(Labo4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(SOURCE_FILES
    Sources/libs/byteswap.h
    Sources/libs/city.cc
    Sources/libs/city.h
    Sources/libs/cityconfig.h
    Sources/libs/sha256.cpp
    Sources/libs/sha256.h
    Sources/Config.h
    Sources/DirectoryCity.cpp
    Sources/DirectoryCity.h
    Sources/DirectoryInt.cpp
    Sources/DirectoryInt.h
    Sources/DirectoryLong.cpp
    Sources/DirectoryLong.h
    Sources/DirectoryPol.h
    Sources/DirectorySha256.cpp
    Sources/DirectorySha256.h
    Sources/DirectoryStl.cpp
    Sources/DirectoryStl.h
    Sources/DirectoryWithoutAVS.cpp
    Sources/DirectoryWithoutAVS.h
    Sources/HashTableTester.h
    Sources/main.cpp
    Sources/Util.cpp
    Sources/Util.h)

add_executable(Labo4 ${SOURCE_FILES})