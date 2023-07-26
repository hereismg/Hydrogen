cmake_minimum_required(VERSION 3.24)
project(hdg)

set(CMAKE_CXX_STANDARD 20)

add_executable(hdg main.cpp res/info.o lib/Lexer.cpp lib/Lexer.h lib/Token.cpp lib/Token.h lib/Shell.cpp lib/Shell.h lib/error/Error.cpp lib/error/Error.h lib/error/IllegalCharError.cpp lib/error/IllegalCharError.h lib/Parser.cpp lib/Parser.h lib/node/Node.cpp lib/node/Node.h lib/node/BinaryOperatorNode.cpp lib/node/BinaryOperatorNode.h lib/Interpreter.cpp lib/Interpreter.h lib/node/UnaryOperatorNode.cpp lib/node/UnaryOperatorNode.h lib/error/RunTimeError.cpp lib/error/RunTimeError.h lib/error/InvalidSyntaxError.cpp lib/error/InvalidSyntaxError.h lib/data_type/Integer.cpp lib/data_type/Integer.h lib/data_type/Float.cpp lib/data_type/Float.h lib/data_type/DataType.cpp lib/data_type/DataType.h lib/node/NumberNode.cpp lib/node/NumberNode.h lib/Position.cpp lib/Position.h)
