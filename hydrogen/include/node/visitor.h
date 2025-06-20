#pragma once

#include "../basic/define.h"

#include "../object/Object.h"
#include "../basic/Environment.h"

namespace hdg{
    class BinOperNode;
    class AssignNode;
    class new_ExeUnitNode;
    class IdentNode;
    class IfStmtNode;
    class WhileStmtNode;
    class New_FuncObjNode;
    class DefNode;
    class ListObjNode;
    class StrNode;
    
    class Visitor{
    protected:
        sObject  m_rVal;
        sObject* m_lVal;
        std::vector<std::shared_ptr<New_Environment>> m_stack;

    public:
        Visitor();

        virtual void visitBinOperNode(BinOperNode& node);
        virtual void visitPostfixNode(PostfixNode& node);

        virtual void visitNumObjNode(NumObjNode& node);
        virtual void visitIntNode(IntNode& node);
        virtual void visitStrNode(StrNode& node) { std::cout << "Visitor::visitStrNode() is not implement!" << std::endl; };
        virtual void visitFuncObjNode(FuncObjNode& node);
        virtual void visitListObjNode(ListObjNode& node);
        virtual void visitIdentNode(IdentNode& node);
        
        virtual void visitAssignNode(AssignNode& node);
        virtual void visitDefNode(DefNode& node);
        virtual void visitFuncDefNode(New_FuncObjNode& node);

        virtual void visitIfStmtNode(IfStmtNode& node);
        virtual void visitWhileStmtNode(WhileStmtNode& node);
        virtual void visitExeUnitNode(new_ExeUnitNode& node);

        virtual sObject  getRVal() { return m_rVal; }
        virtual sObject* getLVal() { return m_lVal; }
        virtual void setRVal(sObject  rVal) { m_rVal = rVal; }
        virtual void setLVal(sObject* lVal) { m_lVal = lVal; }

        virtual std::vector<std::shared_ptr<New_Environment>>& getStack();
        virtual sObject getResult();
        virtual sObject moveResult();

        virtual std::shared_ptr<New_Environment> getCurrentEnvir();
    };

    class InterpreterVisitor: public Visitor{
    protected:

    public:
        void visitBinOperNode(BinOperNode& node) override;
        void visitPostfixNode(PostfixNode& node) override;

        void visitIntNode(IntNode& node) override;
        void visitStrNode(StrNode& node) override;
        void visitFuncObjNode(FuncObjNode& node) override;
        void visitListObjNode(ListObjNode& node) override;
        void visitIdentNode(IdentNode& node) override;

        void visitAssignNode(AssignNode& node) override;
        void visitDefNode(DefNode& node) override;
        void visitFuncDefNode(New_FuncObjNode& node) override;

        void visitIfStmtNode(IfStmtNode& node) override;
        void visitWhileStmtNode(WhileStmtNode& node) override;
        void visitExeUnitNode(new_ExeUnitNode& node) override;
    };
}
