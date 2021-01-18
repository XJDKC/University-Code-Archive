cmake_minimum_required(VERSION 3.14)
project(MIF)

set(CMAKE_CXX_STANDARD 14)

add_executable(MIF main.cpp MIFParser.h MIFParser.cpp MIF.h MIF.cpp)