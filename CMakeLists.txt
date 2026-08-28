cmake_minimum_required(VERSION 4.1)
project(SmartLibrarySystem)

set(CMAKE_CXX_STANDARD 20)

add_executable(SmartLibrarySystem main.cpp
        cmake-build-debug/funcs.h
        funcs.cpp
        Book.cpp
        Book.h)
