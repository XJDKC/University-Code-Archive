cmake_minimum_required(VERSION 3.14)
project(PP1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(samples)
include_directories(src)

add_executable(PP1
        src/errors.cc
        src/errors.h
        src/location.h
        src/main.cc
        src/scanner.h
        src/utility.cc
        src/utility.h)
