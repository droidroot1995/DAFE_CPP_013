cmake_minimum_required(VERSION 2.8)
project(Calculator_2_0)
if ( CMAKE_COMPILER_IS_GNUCXX )
    set (CMAKE_CXX_FLAGS "-I/usr/include/python3.8 main.cpp -lpython")
else ()
    message (FATAL_ERROR "I can't find G++!")
endif ()
file (GLOB COMMON_SRC *.*)
set (SOURCE ${COMMON_SRC})

file (GLOB ARM_SRC arm/*.*)
file (GLOB OPENRISC_SRC openrisc/*.*)

# Платформозависимые исходники
EXECUTE_PROCESS( COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCH )

if (ARCH STREQUAL "arm")
    set (SOURCE "${SOURCE} ${ARM_SRC}")
elseif (ARCH STREQUAL "openrisc")
    set (SOURCE "${SOURCE} ${OPENRISC_SRC}")
endif()

#Финальный штрих и сборка.
add_executable(${PROJECT} ${SOURCE})
