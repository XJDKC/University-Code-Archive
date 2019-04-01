cmake_minimum_required(VERSION 3.13)
project(Exp5)

set(CMAKE_CXX_STANDARD 14)

add_executable(Exp5 main.cpp Blocks.h user.h FCB.h Blocks.cpp FCB.cpp user.cpp myFS.h myFS.cpp)