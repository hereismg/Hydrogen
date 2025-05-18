#ifndef VISITOR_H
#define VISITOR_H

#include "../object/Object.h"
#include "../basic/Environment.h"

namespace hdg{
    class BinOperNode;
    class NumObjNode;
    class IntNode;
    class new_AssignNode;
    class new_ExeUnitNode;
    class IdentNode;
    
    class Visitor{
    protected:
        sObject m_res;
        New_Environment m_envir;

    public:
        virtual void visitBinOperNode(BinOperNode& node);
        virtual void visitNumObjNode(NumObjNode& node);
        virtual void visitIntNode(IntNode& node);
        virtual void visitIdentNode(IdentNode& node);
        virtual void visitAssignNode(new_AssignNode& node);
        virtual void visitExeUnitNode(new_ExeUnitNode& node);

        virtual sObject getResult();
        virtual sObject moveResult();

        virtual New_Environment& getEnvironment();
    };

    class InterpreterVisitor: public Visitor{
    protected:

    public:
        void visitBinOperNode(BinOperNode& node) override;
        void visitIntNode(IntNode& node) override;
        void visitIdentNode(IdentNode& node) override;
        void visitAssignNode(new_AssignNode& node) override;
        void visitExeUnitNode(new_ExeUnitNode& node) override;
    };
}

#endif