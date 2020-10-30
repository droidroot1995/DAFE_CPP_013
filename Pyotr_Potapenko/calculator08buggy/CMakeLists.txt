cmake_minimum_required(VERSION 3.5)

project(calculator08buggy LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(calculator08buggy calculator08buggy.cpp std_lib_facilities.h token.h tokenStream.h variables.h calculateProcess.h)
