cmake_minimum_required(VERSION 4.1)
project(SmartLibrarySystem)

set(CMAKE_CXX_STANDARD 20)

add_executable(SmartLibrarySystem main.cpp
        headers/funcs.h
        source/funcs.cpp
        source/Book.cpp
        headers/Book.h)