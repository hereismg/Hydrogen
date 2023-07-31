//
// Created by Magnesium on 2023/7/22.
//

#include "../../include/node/UnaryOperatorNode.h"

namespace hdg {

    UnaryOperatorNode::UnaryOperatorNode(TokenType oper, Node* obj, const Position& position):
            Node(position), m_oper(oper), m_obj(obj){
    }

    UnaryOperatorNode::~UnaryOperatorNode() {
        delete m_obj;
    }

    void UnaryOperatorNode::setOperator(TokenType oper){
        this->m_oper = oper;
    }
    void UnaryOperatorNode::setObject(Node* obj){
        this->m_obj = obj;
    }

    TokenType UnaryOperatorNode::getOperator(){
        return m_oper;
    }
    Node* UnaryOperatorNode::getObject(){
        return m_obj;
    }

    std::string UnaryOperatorNode::toString() {
        return "(" + tokenTypeName[m_oper] + ", " + m_obj->toString() + ")";
    }

    DataType* UnaryOperatorNode::interpret() {
        DataType* value = m_obj->interpret();

        if (m_oper == MINUS){
            if (value->typeName == DT_INTEGER){
                int num = -((Integer*)value)->getValue();
                delete value;
                return new Integer(num);
            }
            else if (value->typeName == DT_FLOAT){
                double num = -((Float*)value)->getValue();
                delete value;
                return new Float(num);
            }
        }
        else if(m_oper == PLUS){
            return value;
        }
    }
} // hdg