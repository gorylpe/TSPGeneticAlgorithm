cmake_minimum_required(VERSION 3.7)
project(TSPGeneticAlgorithm)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.c
        genetic.c
        genetic.h
        startingsolution.c
        startingsolution.h
        swap2opt.c
        swap2opt.h
        util.c
        util.h)

add_executable(TSPGeneticAlgorithm ${SOURCE_FILES})