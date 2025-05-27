//
// Created by Magnesium on 2023/7/19.
//

#ifndef HDG_NODE_H
#define HDG_NODE_H

#include <string>
#include <memory>
#include <nlohmann/json.hpp>

#include "../object/Object.h"
#include "../basic/Position.h"
#include "../basic/Environment.h"
#include "visitor.h"

namespace hdg {
    class Node {
    protected:
        Position m_position;
        Environment* m_environment{};

    public:
        Node();
        explicit Node(const Position& position);
        Node(const Position& position, Environment* environment);
        virtual ~Node() = 0;

        Position* thisPosition();
        Environment* thisEnvironment();

        virtual std::string toString() = 0;
        virtual Object* interpret() = 0;
        virtual void accept(Visitor& visitor); // TODO 这里设为纯虚函数
    };

    typedef std::unique_ptr<Node> uNode;
} // hdg

#endif //HDG_NODE_H
