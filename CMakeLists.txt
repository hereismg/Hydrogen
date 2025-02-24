cmake_minimum_required(VERSION 3.24)
project(hdg)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH})

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

add_executable(hdg main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/res/info.o ${SOURCES} ${INCLUDES})
add_library(libhdg SHARED ${SOURCES} ${INCLUDES})
target_include_directories(hdg PUBLIC include/basic include/error include/kernel include/node include/object)
target_include_directories(libhdg PUBLIC include/basic include/error include/kernel include/node include/object)

# 添加测试框架
enable_testing()
add_subdirectory(tests)
