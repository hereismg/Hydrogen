//
// Created by Magnesium on 2023/8/9.
//

#ifndef HDG_OBJECTNODE_H
#define HDG_OBJECTNODE_H

#include "Node.h"
#include "../object/String.h"

namespace hdg {
    class ObjAssignNode;
    class Function;
    class New_BaseFunction;

    class ObjectNode: public Node{
    protected:
        std::string m_class;

    public:
        ObjectNode();
        ObjectNode(std::string className, const Position& position, Environment* environment);
        ObjectNode(const Position& position, Environment* environment);
        ~ObjectNode() override;

        void setClass(const std::string& className);
        std::string getClass();

        virtual std::string toString() override = 0;
        virtual Object* interpret() override = 0;
    };

    class FuncObjNode: public ObjectNode {
    protected:
        std::string m_name;
        std::vector<ObjAssignNode*> m_args;
        Node* m_body{};

        sObject m_funcObj;

    public:
        FuncObjNode();
        FuncObjNode(sObject funcObj, const Position& pos);
        FuncObjNode(const Position& position, Environment* parent);
        ~FuncObjNode() override;

        void setArg(ObjAssignNode* arg);
        void setBody(Node* body);
        void setName(const std::string& name);

        sObject getObj();

        virtual std::string toString() override;
        virtual Object* interpret() override;
        virtual void accept(Visitor& visitor) override;
    };

    class NumObjNode: public ObjectNode{
    protected:
        union{
            int64_t i;
            double f;
        }m_value;

    public:
        NumObjNode(int64_t value, const Position& position);
        NumObjNode(float value, const Position& position);
        NumObjNode(double value, const Position& position);
        ~NumObjNode() override;

        std::string toString() override;
        Object* interpret() override;
    };

    class StrNode: public ObjectNode{
    protected:
        std::string m_value;

    public:
        StrNode();
        StrNode(std::string value, const Position& pos);
        StrNode(std::string value, const Position& position, Environment* environment);
        ~StrNode() override;

        void setValue(const std::string& value);
        std::string getValue()const { return m_value; }

        virtual nlohmann::json toJSON() const override;
        
        virtual std::string toString() override;
        virtual Object* interpret() override;
        virtual void accept(Visitor& visitor) override;
    };

    class IntNode: public ObjectNode{
    protected:
        int64_t m_val;

    public:
        explicit IntNode(int64_t val);
        IntNode(int64_t val, const Position& pos);

        IntNode(const IntNode&) = delete;
        IntNode& operator=(const IntNode&) = delete;

        IntNode(IntNode&&) noexcept = default;
        IntNode& operator=(IntNode&&) noexcept = default;

        int64_t getValue() const { return m_val; }
        void setValue(int64_t new_val);

        virtual nlohmann::json toJSON() const override;
        virtual std::string toString() override;
        virtual Object* interpret() override;
        virtual void accept(Visitor& visitor) override;
    };

    class IdentNode: public Node{
    protected:
        std::string m_ident;

    public:
        explicit IdentNode(std::string ident);
        IdentNode(std::string ident, const Position& pos);

        IdentNode(const IdentNode&) = delete;
        IdentNode& operator=(const IdentNode&) = delete;
        IdentNode(IdentNode&&) noexcept = default;
        IdentNode& operator=(IdentNode&&) noexcept = default;

        std::string& getIdent();
        void setIdent(std::string new_ident);

        virtual nlohmann::json toJSON() const override;
        virtual std::string toString() override;
        virtual Object* interpret() override;
        virtual void accept(Visitor& visitor) override;
    };

    class New_FuncObjNode: public ObjectNode{
    protected:
        std::vector<std::string> m_args;
        uNode m_body;

    public:
        New_FuncObjNode(std::vector<std::string>&& args, uNode&& body, const Position& pos);

        std::vector<std::string> getArgs() { return m_args; }
        uNode moveBody() { return std::move(m_body); }

        nlohmann::json toJSON() const override;
        std::string toString() override;
        Object* interpret() override;
        void accept(Visitor& visitor) override;
    };

    class ListObjNode: public ObjectNode {
    protected:
        std::vector<uNode> m_exprList;

    public:
        ListObjNode(std::vector<uNode>&& exprList);
        ListObjNode(std::vector<uNode>&& exprList, const Position& pos);

        std::vector<uNode>& getExprList() { return m_exprList; }

        nlohmann::json toJSON() const override;
        std::string toString() override;
        Object* interpret() override;
        void accept(Visitor& visitor) override;
    };
} // hdg

#endif //HDG_OBJECTNODE_H
