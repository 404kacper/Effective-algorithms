cmake_minimum_required(VERSION 3.21)
project(Lista3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS " -static")

add_executable(Lista3 utilities/FileReader.h utilities/menu.cpp utilities/menu.h main.cpp algorithms/test.h algorithms/GeneticAlgorithm.cpp algorithms/GeneticAlgorithm.h algorithms/Graph.cpp algorithms/Graph.h algorithms/Chromosome.cpp algorithms/Chromosome.h)
