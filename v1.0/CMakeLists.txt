cmake_minimum_required(VERSION 3.10)
project(StudentuRusiavimas VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(SOURCES
    main.cpp
    io_utils.cpp
)

add_executable(studentu_programa ${SOURCES})
