//
// Created by Magnesium on 2023/8/10.
//

#include "../../../include/node/object_node/FuncObjNode.h"

namespace hdg {
    FuncObjNode::FuncObjNode(){
        m_name = "anonymous";
        m_environment = new Environment;
    }

    FuncObjNode::FuncObjNode(const Position &position, Environment *parent) :
        ObjectNode(position, new Environment(parent, parent->getFilePath(), "anonymous")),
        m_name("anonymous") {}

    /**
     * @details     FunObjNode类的主要功能是构建函数对象。在构建过程中，需要函数环境和函数体以及参数变量。
     *              函数环境、函数体和参数变量直接传入新创建的对象中。
     *              故这些数据的生存周期由新创建的对象控制，FuncObjNode不负责管理。
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

    /**
     * @details     这里的 interpret 函数更像是“组装”，将已有的数据组装成一个完整的函数。
     * @note        记得更新环境的文件路径和模块名称。
     * */

    Object *FuncObjNode::interpret() {
        m_environment->setModuleName(m_name);
        return new Function(m_name, m_args, m_environment, m_body, m_position);
    }
} // hdg
