cmake_minimum_required(VERSION 3.24)
project(hdg)

set(CMAKE_CXX_STANDARD 20)

add_executable(hdg res/info.o
        include/object/function/BaseFunction.h
        src/object/function/BaseFunction.cpp
        include/object/function/BuiltInFunction.h
        src/object/function/BuiltInFunction.cpp
        src/main.cpp
        src/Lexer.cpp
        include/Lexer.h
        src/basic/Token.cpp
        include/basic/Token.h src/Shell.cpp include/Shell.h src/error/Error.cpp include/error/Error.h src/error/IllegalCharError.cpp include/error/IllegalCharError.h src/Parser.cpp include/Parser.h src/node/Node.cpp include/node/Node.h src/node/BinaryOperatorNode.cpp include/node/BinaryOperatorNode.h src/Interpreter.cpp include/Interpreter.h src/node/UnaryOperatorNode.cpp include/node/UnaryOperatorNode.h src/error/RuntimeError.cpp include/error/RuntimeError.h src/error/InvalidSyntaxError.cpp include/error/InvalidSyntaxError.h src/object/Integer.cpp include/object/Integer.h src/object/Float.cpp include/object/Float.h src/object/Object.cpp include/object/Object.h src/node/object_node/NumObjNode.cpp include/node/object_node/NumObjNode.h src/basic/Position.cpp include/basic/Position.h src/basic/Environment.cpp include/basic/Environment.h src/node/ObjAccessNode.cpp include/node/ObjAccessNode.h src/node/ObjAssignNode.cpp include/node/ObjAssignNode.h src/node/IfNode.cpp include/node/IfNode.h src/object/None.cpp include/object/None.h src/node/ForNode.cpp include/node/ForNode.h src/node/WhileNode.cpp include/node/WhileNode.h src/object/function/Function.cpp include/object/function/Function.h src/object/List.cpp include/object/List.h src/object/String.cpp include/object/String.h src/error/NotImplementedError.cpp include/error/NotImplementedError.h src/node/object_node/ObjectNode.cpp include/node/object_node/ObjectNode.h src/node/object_node/FuncObjNode.cpp include/node/object_node/FuncObjNode.h src/node/CallNode.cpp include/node/CallNode.h src/node/object_node/StrObjNode.cpp include/node/object_node/StrObjNode.h src/node/StatementsNode.cpp include/node/StatementsNode.h src/error/ZeroDivisionError.cpp include/error/ZeroDivisionError.h)
