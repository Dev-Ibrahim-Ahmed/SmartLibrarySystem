cmake_minimum_required(VERSION 3.16)
project(SmartLibrarySystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

add_executable(SmartLibrarySystem
    main.cpp
    include/Person.h
    src/Person.cpp
    include/Member.h
    src/Member.cpp
    include/Librarian.h
    src/Librarian.cpp
    include/Book.h
    src/Book.cpp
    include/funcs.h
    src/funcs.cpp
    include/resizableArray.h
    include/DataManager.h
    src/DataManager.cpp
    include/json.hpp
        include/menus.h
        src/menus.cpp
)