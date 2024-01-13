cmake_minimum_required(VERSION 3.24)
project(hdg)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

add_executable(hdg src/main.cpp ${SOURCES} ${INCLUDES})
