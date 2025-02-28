//
// Created by Magnesium on 2023/8/9.
//

#include "../../include/node/ObjectNode.h"
#include "../../include/object/function/Function.h"

namespace hdg {
    ObjectNode::ObjectNode() = default;

    ObjectNode::ObjectNode(std::string className, const Position &position, Environment *environment)
        : Node(position, environment), m_class(std::move(className)){}

    ObjectNode::ObjectNode(const Position &position, Environment *environment) :
        Node(position, environment) {}

    ObjectNode::~ObjectNode() = default;

    void ObjectNode::setClass(const std::string &className) {
        m_class = className;
    }

    std::string ObjectNode::getClass() {
        return m_class;
    }

    NumObjNode::NumObjNode(long long value, const Position& position):
            ObjectNode("Integer", position, nullptr), m_value({.i = value}){}

    NumObjNode::NumObjNode(float value, const Position& position):
            ObjectNode("Float", position, nullptr), m_value({.f = value}){}

    NumObjNode::NumObjNode(double value, const Position& position):
            ObjectNode("Float", position, nullptr), m_value({.f = value}){}

    NumObjNode::~NumObjNode() = default;


    std::string NumObjNode::toString() {
        if (m_class == "Integer"){
            return std::to_string(m_value.i);
        }
        else if (m_class == "Float") {
            return std::to_string(m_value.f);
        }
        else{
            std::cout << "NumObjNode::toString: Unknown class type." << std::endl;
        }
    }

    Object *NumObjNode::interpret() {
        if (m_class == "Integer"){
            return new Integer(m_value.i, m_position);
        }
        else if (m_class == "Float") {
            return new Float(m_value.f, m_position);
        }
        else{
            std::cout << "NumObjNode::interpret: Unknown class type." << std::endl;
        }
    }

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

    StrObjNode::StrObjNode() {
        setClass("String");
    }

    StrObjNode::StrObjNode(std::string value, const Position &position, Environment *environment) :
            ObjectNode("String", position, environment), m_value(std::move(value)) {}

    StrObjNode::~StrObjNode() = default;

    void StrObjNode::setValue(const std::string& value) {
        m_value = value;
    }

    std::string StrObjNode::toString() {
        return "StrObjNode(\"" + m_value + "\"";
    }

    Object *StrObjNode::interpret() {
        return new String(m_value, m_position);
    }
} // hdg