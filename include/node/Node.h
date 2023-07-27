//
// Created by Magnesium on 2023/7/19.
//

#ifndef HDG_NODE_H
#define HDG_NODE_H

#include<string>
#include"../data_type/DataType.h"
#include "../basic/Position.h"


namespace hdg {

    class Node {
    protected:
        Position m_position;

    public:
        Node(const std::string& context, int posStart, int posEnd);
        Node(const Position& position);

        Position& thisPosition();

        virtual std::string toString();
        virtual DataType* interpret();
    };

} // hdg

#endif //HDG_NODE_H
