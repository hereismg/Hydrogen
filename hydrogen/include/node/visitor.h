#ifndef VISITOR_H
#define VISITOR_H

namespace hdg{
    class Object;

    class BinOperNode;
    class NumObjNode;
    class IntNode;
    
    class Visitor{
    public:
        virtual void visitBinOperNode(BinOperNode& node);
        virtual void visitNumObjNode(NumObjNode& node);
        virtual void visitIntNode(IntNode& node);
    };

    class InterpreterVisitor: public Visitor{
    protected:
        Object* res;

    public:
        void visitBinOperNode(BinOperNode& node) override;
        void visitIntNode(IntNode& node) override;
    };
}

#endif