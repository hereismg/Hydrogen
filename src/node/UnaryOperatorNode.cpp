//
// Created by Magnesium on 2023/7/22.
//

#include "../../include/node/UnaryOperatorNode.h"

namespace hdg {

    UnaryOperatorNode::UnaryOperatorNode(TokenType oper, Node* obj, const Position& position, Environment* environment):
            Node(position, environment), m_oper(oper), m_obj(obj){
    }

    UnaryOperatorNode::UnaryOperatorNode(Token oper, Node *obj, const Position &position, Environment* environment):
        Node(position, environment), m_oper(oper), m_obj(obj){

    }

    UnaryOperatorNode::~UnaryOperatorNode() {
        delete m_obj;
    }

    void UnaryOperatorNode::setOperator(const Token& oper){
        this->m_oper = oper;
    }
    void UnaryOperatorNode::setObject(Node* obj){
        this->m_obj = obj;
    }

    Token UnaryOperatorNode::getOperator(){
        return m_oper;
    }
    Node* UnaryOperatorNode::getObject(){
        return m_obj;
    }

    std::string UnaryOperatorNode::toString() {
        return "(" + tokenTypeName[m_oper.getType()] + ", " + m_obj->toString() + ")";
    }

    Object* UnaryOperatorNode::interpret() {
        Object* value = m_obj->interpret();

        if (m_oper.getType() == MINUS){
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
        else if(m_oper.getType() == PLUS){
            return value;
        }
        else if(m_oper.match(KEYWORD, "not")){
            return  value->notOperator();
        }
    }

} // hdg