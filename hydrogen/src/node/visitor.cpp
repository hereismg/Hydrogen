#include "../../include/node/visitor.h"

#include <iostream>

#include "../../include/node/BinaryOperatorNode.h"

namespace hdg{
    void Visitor::visitBinOperNode(BinOperNode& node){
        std::cout << "Visitor::visitBinOperNode() is not implement!" << std::endl;
    }

    void Visitor::visitNumObjNode(NumObjNode& node){
        std::cout << "Visitor::visitNumObjNode() is not implement!" << std::endl;
    }

    void InterpreterVisitor::visitBinOperNode(BinOperNode& node){
    }
}
