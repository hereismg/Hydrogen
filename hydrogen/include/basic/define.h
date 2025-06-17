#ifndef DEFINE_H
#define DEFINE_H

#include <memory>

namespace hdg{
    class Node;
    typedef std::unique_ptr<Node> uNode;

    class BinOperNode;
    class PostfixNode;

    class new_AssignNode;
    class new_IfStmtNode;
    class new_WhileStmtNode;
    class new_ExeUnitNode;
    
    class NumObjNode;
    class IntNode;
    class FuncObjNode;

    class Visitor;
    class InterpreterVisitor;

    class Object;
    typedef std::unique_ptr<Object> uObject;
    typedef std::shared_ptr<Object> sObject;
    typedef std::weak_ptr<Object>   wObject;

    class Integer;
    class String;
    class Float;

    class New_Environment;

    typedef int     i32;
    typedef int64_t i64;
}

#endif
