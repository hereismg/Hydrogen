//
// Created by Magnesium on 2023/7/19.
//

#ifndef HDG_NODE_H
#define HDG_NODE_H

#include <string>
#include "../object/Object.h"
#include "../basic/Position.h"
#include "../basic/Environment.h"


namespace hdg {

    class Node {
    protected:
        Position m_position;
        Environment* m_environment;

    public:
        explicit Node(const Position& position);
        Node(const Position& position, Environment* environment);
        virtual ~Node() = 0;

        Position* thisPosition();
        Environment* thisEnvironment();

        virtual std::string toString() = 0;
        virtual Object* interpret() = 0;
    };

} // hdg

#endif //HDG_NODE_H
