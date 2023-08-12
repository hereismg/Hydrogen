//
// Created by Magnesium on 2023/8/10.
//

#include "../../../include/node/object_node/FuncObjNode.h"

namespace hdg {
    FuncObjNode::FuncObjNode():
        m_name("anonymous"){
        m_environment = new Environment("function", nullptr);}

    FuncObjNode::FuncObjNode(const Position &position, Environment *parent) :
        ObjectNode(position, new Environment("function", parent)), m_name("anonymous") {}

    /* FunObjNode类的主要功能是构建函数对象。在构建过程中，需要函数环境和函数体以及参数变量。
     * 函数环境、函数体和参数变量直接传入新创建的对象中
     * 故这些数据的生存周期由新创建的对象控制，FuncObjNode不负责管理
     * */
    FuncObjNode::~FuncObjNode() = default;

    void FuncObjNode::setArg(ObjAssignNode *arg) {
        m_args.push_back(arg);
    }

    void FuncObjNode::setBody(Node *body) {
        m_body = body;
    }

    void FuncObjNode::setName(const std::string& name) {
        m_name = name;
    }

    std::string FuncObjNode::toString() {
        return m_name;
    }

    Object *FuncObjNode::interpret() {
        return new Function(m_name, m_args, m_environment, m_body, m_position);
    }
} // hdg