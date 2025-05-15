#ifndef VISITOR_H
#define VISITOR_H

#include "../object/Object.h"

namespace hdg{
    class BinOperNode;
    class NumObjNode;
    class IntNode;
    
    class Visitor{
    protected:
        uObject m_res;

    public:
        virtual void visitBinOperNode(BinOperNode& node);
        virtual void visitNumObjNode(NumObjNode& node);
        virtual void visitIntNode(IntNode& node);

        virtual uObject& getResult();
        virtual uObject  moveResult();
    };

    class InterpreterVisitor: public Visitor{
    public:
        void visitBinOperNode(BinOperNode& node) override;
        void visitIntNode(IntNode& node) override;
    };
}

#endif