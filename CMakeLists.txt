cmake_minimum_required(VERSION 3.24)
project(hdg)

set(CMAKE_CXX_STANDARD 20)

add_executable(hdg res/info.o src/main.cpp src/Lexer.cpp include/Lexer.h src/basic/Token.cpp include/basic/Token.h src/Shell.cpp include/Shell.h src/error/Error.cpp include/error/Error.h src/error/IllegalCharError.cpp include/error/IllegalCharError.h src/Parser.cpp include/Parser.h src/node/Node.cpp include/node/Node.h src/node/BinaryOperatorNode.cpp include/node/BinaryOperatorNode.h src/Interpreter.cpp include/Interpreter.h src/node/UnaryOperatorNode.cpp include/node/UnaryOperatorNode.h src/error/RunTimeError.cpp include/error/RunTimeError.h src/error/InvalidSyntaxError.cpp include/error/InvalidSyntaxError.h src/data_type/Integer.cpp include/data_type/Integer.h src/data_type/Float.cpp include/data_type/Float.h src/data_type/DataType.cpp include/data_type/DataType.h src/node/NumberNode.cpp include/node/NumberNode.h src/basic/Position.cpp include/basic/Position.h src/basic/Environment.cpp include/basic/Environment.h src/node/VariableAccessNode.cpp include/node/VariableAccessNode.h src/node/VariableAssignNode.cpp include/node/VariableAssignNode.h)
