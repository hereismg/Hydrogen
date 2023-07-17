cmake_minimum_required(VERSION 3.24)
project(hdg)

set(CMAKE_CXX_STANDARD 20)

add_executable(hdg main.cpp lib/Lexer.cpp lib/Lexer.h lib/Token.cpp lib/Token.h lib/Shell.cpp lib/Shell.h lib/error/Error.cpp lib/error/Error.h lib/error/IllegalCharError.cpp lib/error/IllegalCharError.h lib/Parser.cpp lib/Parser.h)
