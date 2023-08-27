//
// Created by Magnesium on 2023/8/2.
//

#include "../../include/node/ForNode.h"

namespace hdg {
    ForNode::ForNode(const Token &index, int to, const Position &position, Environment *parent):
            Node(position, new Environment(parent, parent->getFilePath(), parent->getModuleName())),
            m_index(index), m_from(0), m_to(to), m_step(1){}

    ForNode::ForNode(const Token &index, int from, int to, int step, Node *expr,
                     const Position &position, Environment *parent):
            Node(position, new Environment(parent, parent->getFilePath(), parent->getModuleName())),
            m_index(index), m_from(from), m_to(to), m_step(step), m_expr(expr){}

    ForNode::~ForNode() {
        delete m_environment;
        delete m_expr;
    }

    void ForNode::setIndex(const Token &index) {
        m_index = index;
    }

    void ForNode::setFrom(int from) {
        m_from = from;
    }

    void ForNode::setTo(int to) {
        m_to = to;
    }

    void ForNode::setExpr(Node *expr) {
        m_expr = expr;
    }

    void ForNode::setStep(int step) {
        m_step = step;
    }

    std::string ForNode::toString() {
        return "for";
    }

    Object *ForNode::interpret() {
        auto* index = new Integer(m_from);
        Object* result;
        m_environment->setSymbol(m_index.getValue(), index, 1); /// 本地模式

        if (m_from <= m_to){
            while(index->getValue() <= m_to){
                result = m_expr->interpret();
                index->setValue(index->getValue()+m_step);
            }
        }
        else{
            while(index->getValue() >= m_to){
                result = m_expr->interpret();
                index->setValue(index->getValue()-m_step);
            }
        }

        return result;
    }
} // hdg