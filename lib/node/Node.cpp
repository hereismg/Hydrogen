//
// Created by Magnesium on 2023/7/19.
//

#include "Node.h"

namespace hdg {

    Node::Node(const std::string& context, int posStart, int posEnd):
            position(context, posStart, posEnd){
    }

    Node::Node(const Position &position) :
            position(position){

    }

    std::string Node::toString() {
        return "NULL";
    }

    DataType* Node::interpret() {
        return nullptr;
    }

    Position &Node::thisPosition() {
        return position;
    }

} // hdg