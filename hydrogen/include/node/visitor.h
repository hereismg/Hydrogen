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
    class new_IfStmtNode;
    class new_WhileStmtNode;
    
    class Visitor{
    protected:
        sObject m_res;
        std::vector<std::shared_ptr<New_Environment>> m_stack;

    public:
        Visitor();

        virtual void visitBinOperNode(BinOperNode& node);
        virtual void visitNumObjNode(NumObjNode& node);
        virtual void visitIntNode(IntNode& node);
        virtual void visitIdentNode(IdentNode& node);
        
        virtual void visitAssignNode(new_AssignNode& node);
        virtual void visitIfStmtNode(new_IfStmtNode& node);
        virtual void visitWhileStmtNode(new_WhileStmtNode& node);
        virtual void visitExeUnitNode(new_ExeUnitNode& node);

        virtual std::vector<std::shared_ptr<New_Environment>>& getStack();
        virtual sObject getResult();
        virtual sObject moveResult();

        virtual std::shared_ptr<New_Environment> getCurrentEnvir();
    };

    class InterpreterVisitor: public Visitor{
    protected:

    public:
        void visitBinOperNode(BinOperNode& node) override;
        void visitIntNode(IntNode& node) override;
        void visitIdentNode(IdentNode& node) override;

        void visitAssignNode(new_AssignNode& node) override;
        void visitIfStmtNode(new_IfStmtNode& node) override;
        void visitWhileStmtNode(new_WhileStmtNode& node) override;
        void visitExeUnitNode(new_ExeUnitNode& node) override;
    };
}

#endif