//
// Created by Magnesium on 2023/8/11.
//

#include "../../include/node/CallNode.h"

namespace hdg {
    CallNode::CallNode() = default;

    CallNode::CallNode(Node* call, std::vector<Node *> list, Token::Type oper, const Position &position,
                       Environment *environment):
       Node(position, environment), m_call(call), m_list(std::move(list)), m_oper(oper){}


    CallNode::CallNode(const Position &position, Environment *environment):
        Node(position, environment){}

    CallNode::~CallNode() = default;

    void CallNode::addNode(Node *node) {
        m_list.push_back(node);
    }

    void CallNode::setOperator(Token::Type oper) {
        m_oper = oper;
    }

    void CallNode::setCall(Node* call) {
        m_call = call;
    }

    std::string CallNode::toString() {
        return "CallNode";
    }

    /**
     * @details
     * */
    Object *CallNode::interpret() {
        /// 这里主要干了两件事情：\n\n
        ///     1、解析被呼叫元素 call\n\n
        ///     2、解析参数
        Object* obj = m_call->interpret();
        std::vector<Object*> objList;
        objList.reserve(m_list.size());
        for (auto & i : m_list) objList.push_back(i->interpret());

        /// 此时开始运行parenthesis，并且监听异常。
        try{
            if (m_oper == Token::LPAREN){
                return obj->parenthesis(objList);
            }
            else{
                throw RuntimeError(
                        "Error",
                        m_position
                );
            }
        }
        catch (Error& error){
            error.thisPosStack()->push_back(m_position);
            throw error;
        }

    }

} // hdg