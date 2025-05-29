cmake_minimum_required(VERSION 3.24)
project(hdg)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}")

# Boost.sml
set(SML_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/boost")

# Google Test
add_subdirectory("lib/gtest-1.16")
set(GTEST_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/gtest-1.16/googlemock" "${CMAKE_CURRENT_SOURCE_DIR}/lib/gtest-1.16/googletest")

# nlohmann/json
set(LIB_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/lib")


if (CMAKE_CXX_COMPILE_ID STREQUAL "GNU")
    add_compile_options(
        libhdg 
        PRIVATE 
        -Wall -Wextra
        -Werror
        -Wno-unused-parameter
        -Wno-deprecated-copy
        -Wno-unused-variable
        -Werror=return-type   # 将返回值警告转为错误
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(
        libhdg 
        PRIVATE 
        /utf-8  # 使 MSVC 使用 UTF-8 字符集
        /Zc:__cplusplus # 正确报告 __cplusplus 值
    )
endif()


add_subdirectory(hydrogen)
add_subdirectory(shell)
add_subdirectory(clt)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# 添加测试框架
enable_testing()
add_subdirectory("tests")
