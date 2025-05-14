#ifndef VISITOR_H
#define VISITOR_H

namespace hdg{
    class BinOperNode;
    class NumObjNode;

    class Visitor{
    public:
        virtual void visitBinOperNode(BinOperNode& node);
        virtual void visitNumObjNode(NumObjNode& node);
    };

    class InterpreterVisitor{
    public:
        void visitBinOperNode(BinOperNode& node);
    };
}

#endif