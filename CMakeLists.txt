cmake_minimum_required(VERSION 3.24)

project(AoC23 DESCRIPTION "Advent of Code 2023 in C++"
              LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_COLOR_DIAGNOSTICS ON)

find_package(fmt REQUIRED)
include(FetchContent)
FetchContent_Declare(
    nanobench
    GIT_REPOSITORY https://github.com/martinus/nanobench.git
    GIT_TAG v4.1.0
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(nanobench)

add_library(aoc23_utils src/aoc23_utils.cpp)
target_include_directories(aoc23_utils PRIVATE include)
target_link_libraries(aoc23_utils PRIVATE fmt::fmt)

add_executable(day1 src/day01.cpp)
target_include_directories(day1 PRIVATE include)
target_link_libraries(day1 PRIVATE aoc23_utils fmt::fmt nanobench)
target_compile_features(day1 PUBLIC cxx_std_23)
