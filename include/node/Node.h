//
// Created by Magnesium on 2023/7/19.
//

#ifndef HDG_NODE_H
#define HDG_NODE_H

#include <string>
#include "../data_type/DataType.h"
#include "../basic/Position.h"
#include "../basic/Environment.h"


namespace hdg {

    class Node {
    protected:
        Position m_position;
        Environment* m_environment;

    public:
        Node(const std::string& context, int posStart, int posEnd);
        Node(const Position& position);
        Node(const Position& position, Environment* environment);

        Position& thisPosition();

        virtual std::string toString();
        virtual DataType* interpret();
    };

} // hdg

#endif //HDG_NODE_H
