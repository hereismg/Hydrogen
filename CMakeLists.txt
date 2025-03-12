cmake_minimum_required(VERSION 3.24)
project(hdg)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}")

set(SML_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/boost")

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# hdg 可执行文件
add_executable(hdg main.cpp "${SOURCES}")
target_include_directories(hdg PUBLIC "${SML_INCLUDE_DIR}")

# hdg 库文件，测试框架将会引用该共享库
add_library(libhdg SHARED "${SOURCES}")
target_include_directories(libhdg PUBLIC "${SML_INCLUDE_DIR}")

# 添加测试框架
enable_testing()
add_subdirectory("tests")
