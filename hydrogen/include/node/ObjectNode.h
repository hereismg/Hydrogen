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

        virtual std::string toString() = 0;
        virtual Object* interpret() = 0;
    };

    class FuncObjNode: public ObjectNode {
    protected:
        std::string m_name;
        std::vector<ObjAssignNode*> m_args;
        Node* m_body{};

    public:
        FuncObjNode();
        FuncObjNode(const Position& position, Environment* parent);
        ~FuncObjNode() override;

        void setArg(ObjAssignNode* arg);
        void setBody(Node* body);
        void setName(const std::string& name);

        std::string toString() override;
        Object* interpret() override;
    };

    class NumObjNode: public ObjectNode{
    protected:
        union{
            long long i;
            double f;
        }m_value;

    public:
        NumObjNode(long long value, const Position& position);
        NumObjNode(float value, const Position& position);
        NumObjNode(double value, const Position& position);
        ~NumObjNode() override;

        std::string toString() override;
        Object* interpret() override;
    };

    class StrObjNode: public ObjectNode{
    protected:
        std::string m_value;

    public:
        StrObjNode();
        StrObjNode(std::string value, const Position& position, Environment* environment);
        ~StrObjNode() override;

        void setValue(const std::string& value);

        std::string toString() override;
        Object* interpret() override;
    };
} // hdg

#endif //HDG_OBJECTNODE_H
