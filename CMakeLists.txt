cmake_minimum_required(VERSION 4.1)
project(SmartLibrarySystem)

set(CMAKE_CXX_STANDARD 20)

add_executable(SmartLibrarySystem main.cpp
        VC/headers/funcs.h
        VC/source/funcs.cpp
        VC/source/Book.cpp
        VC/headers/Book.h)