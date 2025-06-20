//
// Created by Magnesium on 2023/8/9.
//

#include "../../include/node/ObjectNode.h"

#include <string>
#include <cassert>

#include "../../include/object/Function.h"
#include "../../include/object/Float.h"

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

    NumObjNode::NumObjNode(int64_t value, const Position& position):
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
            exit(-1);
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
            exit(-1);
        }
    }

    FuncObjNode::FuncObjNode(){
        m_name = "anonymous";
        m_environment = new Environment;
    }
    
    FuncObjNode::FuncObjNode(sObject funcObj, const Position& pos)
        : ObjectNode("Function", pos, nullptr), m_funcObj(funcObj){}

    FuncObjNode::FuncObjNode(const Position &position, Environment *parent) 
        : ObjectNode(position, new Environment(parent, parent->getFilePath(), "anonymous")),
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
    
    sObject FuncObjNode::getObj() {
        return m_funcObj;
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
        return nullptr;
    }

    void FuncObjNode::accept(Visitor& visitor) {
        visitor.visitFuncObjNode(*this);
    }

    StrNode::StrNode() {
        setClass("String");
    }

    StrNode::StrNode(std::string val, const Position& pos):
        ObjectNode("String", pos, nullptr), m_value(std::move(val))    
    {
        setClass("String");
    }

    StrNode::StrNode(std::string value, const Position &position, Environment *environment) :
            ObjectNode("String", position, environment), m_value(std::move(value)) {}

    StrNode::~StrNode() = default;

    nlohmann::json StrNode::toJSON() const {
        return m_value;
    }

    void StrNode::setValue(const std::string& value) {
        m_value = value;
    }

    std::string StrNode::toString() {
        return "StrObjNode(\"" + m_value + "\"";
    }

    Object *StrNode::interpret() {
        return new String(m_value, m_position);
    }

    void StrNode::accept(Visitor& visitor){
        visitor.visitStrNode(*this);
    }

    IntNode::IntNode(int64_t val)
        : m_val(val)
    {
        m_class = "Integer"; // TODO 注意，这最好用 ObjectNode 直接构造，但因为 ObjectNode 的设计缺陷，暂时这样做。
    }

    IntNode::IntNode(int64_t val, const Position& pos)
        : m_val(val)
    {
        m_position = pos;
        m_class = "Integer"; // TODO 注意，这最好用 ObjectNode 直接构造，但因为 ObjectNode 的设计缺陷，暂时这样做。
    }
    
    uIntNode IntNode::create(int64_t val, optional<Position> pos) {
        if (pos.has_value()) return std::make_unique<IntNode>(val, pos.value());
        else return std::make_unique<IntNode>(val);
    }

    void IntNode::setValue(int64_t new_val){
        m_val = new_val;
    }

    std::string IntNode::toString(){
        return std::to_string(m_val);
    }

    nlohmann::json IntNode::toJSON() const {
        // nlohmann::json j{ {"__class__", "IntNode"} };
        // j["val"] = m_val;
        // return j;

        return m_val;
    }

    Object* IntNode::interpret(){
        assert(false && "IntNode has been disabled!");
        return nullptr;
    }

    void IntNode::accept(Visitor& visitor){
        visitor.visitIntNode(*this);
    }

    IdentNode::IdentNode(std::string ident) 
        : m_ident(std::move(ident))
    {
        assert(m_ident != "");
    }

    IdentNode::IdentNode(std::string ident, const Position& pos)
        : Node(pos), m_ident(ident)
    {
        assert(m_ident != "");
    }

    uIdentNode IdentNode::create(std::string ident, optional<Position> pos) {
        if (pos.has_value()) return std::make_unique<IdentNode>(std::move(ident), pos.value());
        else return std::make_unique<IdentNode>(ident);
    }

    std::string& IdentNode::getIdent(){
        return m_ident;
    }

    void IdentNode::setIdent(std::string new_ident){
        // m_ident = std::move(new_ident);
    }

    nlohmann::json IdentNode::toJSON() const {
        return {
            {"__class__", "IdentNode"}, 
            {"val", m_ident}
        };
    }

    std::string IdentNode::toString(){
        return "IDENT:" + m_ident;
    }

    Object* IdentNode::interpret(){
        assert(false);
        return nullptr;
    }

    void IdentNode::accept(Visitor& visitor){
        visitor.visitIdentNode(*this);
    }

    New_FuncObjNode::New_FuncObjNode(std::vector<std::string>&& args, uNode body, const Position& pos)
        : ObjectNode("Function", pos, nullptr), m_args(std::move(args)), m_body(std::move(body))
        {}


    nlohmann::json New_FuncObjNode::toJSON() const {
        nlohmann::json j{{"__class__", "FuncObjNode"}};

        j["args"] = nlohmann::json::array();

        for (auto& s : m_args) {
            j["args"].push_back(s);
        }

        j["body"] = m_body->toJSON();

        return j;
    }

    std::string New_FuncObjNode::toString(){
        return "New_FuncObjNode";
    }

    Object* New_FuncObjNode::interpret(){
        assert(false);
        return nullptr;
    }

    void New_FuncObjNode::accept(Visitor& visitor){
        visitor.visitFuncDefNode(*this);
    }

    ListObjNode::ListObjNode(std::vector<uNode>&& exprList) 
        : m_exprList(std::move(exprList))
    {}
        
    ListObjNode::ListObjNode(std::vector<uNode>&& exprList, const Position& pos) 
        : ObjectNode("ListObjNode", pos, nullptr), m_exprList(std::move(exprList))
    {}
    
    void ListObjNode::accept(Visitor& visitor){
        visitor.visitListObjNode(*this);
    }

    nlohmann::json ListObjNode::toJSON() const {
        nlohmann::json j = {{"__class__", "ListObjNode"}};
        
        j["exprList"] = nlohmann::json::array();

        for (auto& n : m_exprList){
            j["exprList"].push_back(n->toJSON());
        }

        return j;
    }


    std::string ListObjNode::toString(){
        return "ListObjNode";
    }

    Object* ListObjNode::interpret(){
        assert(false);
        return nullptr;
    }

} // hdg