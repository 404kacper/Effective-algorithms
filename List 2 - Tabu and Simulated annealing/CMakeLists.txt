cmake_minimum_required(VERSION 3.21.1)
project(Lista2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS " -static")
add_executable(Lista2 main.cpp utilities/menu.cpp algorithms/SA.cpp algorithms/SA.h algorithms/TS.cpp algorithms/TS.h)
