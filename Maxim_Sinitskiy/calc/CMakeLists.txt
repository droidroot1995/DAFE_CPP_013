cmake_minimum_required(VERSION 3.5)

project(calculator02buggy LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(calculator02buggy calculator02buggy.cpp std_lib_facilities.h)
