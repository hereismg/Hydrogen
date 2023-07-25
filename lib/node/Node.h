//
// Created by Magnesium on 2023/7/19.
//

#include<string>
#include"../data_type/DataType.h"
#include "../Position.h"

#ifndef HDG_NODE_H
#define HDG_NODE_H

namespace hdg {

    class Node {
    protected:
        Position position;

    public:
        Node(const std::string& context, int posStart, int posEnd);
        Node(const Position& position);

        Position& thisPosition();

        virtual std::string toString();
        virtual DataType* interpret();
    };

} // hdg

#endif //HDG_NODE_H
