#include "../../include/node/visitor.h"

#include <iostream>

#include "../../include/node/BinaryOperatorNode.h"
#include "../../include/node/ObjectNode.h"

namespace hdg{
    void Visitor::visitBinOperNode(BinOperNode& node){
        std::cout << "Visitor::visitBinOperNode() is not implement!" << std::endl;
    }

    void Visitor::visitNumObjNode(NumObjNode& node){
        std::cout << "Visitor::visitNumObjNode() is not implement!" << std::endl;
    }

    void Visitor::visitIntNode(IntNode& node){
        std::cout << "Visitor::visitIntNode() is not implement!" << std::endl;
    }


    void InterpreterVisitor::visitBinOperNode(BinOperNode& node){
        // node.getLeft()->accept(*this);


        std::cout << "bin" << std::endl;
    }

    void InterpreterVisitor::visitIntNode(IntNode& node){

    }
}
