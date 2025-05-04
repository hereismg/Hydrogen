cmake_minimum_required(VERSION 3.24)
project(hdg)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")
# set(LIBRARY_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}")

# 设置第三方依赖：Boost.sml
set(SML_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/boost")
add_subdirectory("lib/gtest-1.16")
set(GTEST_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/gtest-1.16/googlemock" "${CMAKE_CURRENT_SOURCE_DIR}/lib/gtest-1.16/googletest")

add_subdirectory(hydrogen)
add_subdirectory(shell)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# 添加测试框架
enable_testing()
add_subdirectory("tests")
