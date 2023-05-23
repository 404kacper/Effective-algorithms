cmake_minimum_required(VERSION 3.21)
project(lista1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(lista1 main.cpp utilities/menu.h utilities/FileReader.h utilities/AdjacencyMatrix.cpp utilities/AdjacencyMatrix.h algorithms/TspDp.cpp algorithms/TspDp.h utilities/stopwatch/Stopwatch.h)
