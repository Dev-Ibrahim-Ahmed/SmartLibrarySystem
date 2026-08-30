cmake_minimum_required(VERSION 4.1)
project(SmartLibrarySystem)

set(CMAKE_CXX_STANDARD 20)

add_executable(SmartLibrarySystem main.cpp
        include/funcs.h
        src/funcs.cpp
        src/Book.cpp
        include/Book.h
        include/Person.h
        include/Member.h
        src/Member.cpp
        src/Person.cpp
        include/resizableArray.h)