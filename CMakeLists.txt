cmake_minimum_required(VERSION 3.24)

project(AoC23 DESCRIPTION "Advent of Code 2023 in C++"
              LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_COLOR_DIAGNOSTICS ON)

find_package(fmt REQUIRED)

add_executable(day1 src/day01.cpp)
target_link_libraries(day1 PRIVATE fmt::fmt)
target_compile_features(day1 PUBLIC cxx_std_23)
