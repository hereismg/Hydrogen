//
// Created by Magnesium on 2023/8/2.
//

#include "../../include/node/ForNode.h"

namespace hdg {

    ForNode::ForNode(const Token &index, int to, const Position &position, Environment *parent):
            Node(position, new Environment("for", parent)), m_index(index), m_from(0), m_to(to), m_step(1){
    }

    ForNode::ForNode(const Token &index, int from, int to, int step, Node *expr,
                     const Position &position, Environment *parent):
            Node(position, new Environment("for", parent)), m_index(index), m_from(from), m_to(to), m_step(step), m_expr(expr){
    }

    ForNode::~ForNode() {
        delete m_environment;
    }

    std::string ForNode::toString() {
        return "for";
    }

    DataType *ForNode::interpret() {
        auto* index = new Integer(m_from);
        DataType* result;
        m_environment->addSymbol(m_index.getValue(), index);

        while(index->getValue() <= m_to){
            result = m_expr->interpret();
            index->setValue(index->getValue()+m_step);
        }

        return result;
    }

} // hdg