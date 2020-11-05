cmake_minimum_required(VERSION 3.17)
project(calcute)

set(CMAKE_CXX_STANDARD 20)

add_executable(calcute main.cpp FUNCTION.cpp FUNCTION.h TOKEN.h TOKEN_STREAM.cpp TOKEN_STREAM.h Variable.cpp Variable.h std_lib_facilities.h)